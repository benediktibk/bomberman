#include "gameengine/router.h"
#include "gameengine/notdangerousandfreedecider.h"
#include "gameengine/coveredbyplayerdecider.h"
#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/coveredbypowerupdecider.h"
#include "gameengine/freedecider.h"
#include "gameengine/routergrid.h"
#include "gameengine/certainfieldandnotdangerousdecider.h"
#include "common/grid.h"
#include <fstream>
#include <assert.h>

using namespace GameEngine;
using namespace Common;
using namespace std;
using namespace boost;

Router::Router(Grid &grid, const GameState &gameState, unsigned int playerID) :
	m_grid(new RouterGrid(grid, gameState, playerID))
{ }

Router::~Router()
{
	delete m_grid;
}

void Router::updatePlayerFields()
{
	m_grid->updatePlayerFlags();
}

Route Router::getRouteToPlayer(const Common::GridPoint &position) const
{
	return getRoute(NotDangerousAndFreeDecider(), CoveredByPlayerDecider(), position);
}

Route Router::getRouteToNotDangerousField(const Common::GridPoint &position) const
{
	return getRoute(FreeDecider(), NotDangerousAndFreeDecider(), position);
}

Route Router::getRouteToLooseWall(const Common::GridPoint &position) const
{
	return getRoute(NotDangerousAndFreeDecider(), CoveredByLooseWallDecider(), position);
}

Route Router::getRouteToPowerUp(const GridPoint &position) const
{
	return getRoute(NotDangerousAndFreeDecider(), CoveredByPowerUpDecider(), position);
}

bool Router::canEscapeFromIfBombPlaced(const GridPoint &position, unsigned int bombRange) const
{
	const Grid &sourceGrid = m_grid->getGrid();
	vector<GridPoint> targets = sourceGrid.getAllFieldsBesideBombRange(position, bombRange);
	Route route = getRoute(NotDangerousAndFreeDecider(), CertainFieldAndNotDangerousDecider(targets), position);

	if (route.getDirection() != PlayerState::PlayerDirectionNone)
		return true;
	else
		return false;
}

void Router::writeDebuggingInformationToFile(DistanceMatrix &distances) const
{
	string fileName = "/var/tmp/ultimatebomberman_distances.csv";
	fstream file(fileName.c_str(), ios_base::out);
	unsigned int height = m_grid->getHeight();
	unsigned int width = m_grid->getWidth();

	file << ";";
	for (unsigned int x = 0; x < width; ++x)
		file << x << ";";
	file << endl;

	for (unsigned int y = 0; y < height; ++y)
	{
		file << y << ";";
		for (unsigned int x = 0; x < width; ++x)
			file << distances[y][x] << ";";

		file << endl;
	}
}

Route Router::getRoute(const RouterGridFieldDecider &canWalkOn,
					   const RouterGridFieldDecider &target,
					   const GridPoint &startPosition) const
{
	const RouterGridField &startField = m_grid->getField(startPosition);

	if (target.decide(startField, startField, false))
		return Route(0, PlayerState::PlayerDirectionNone);

	bool targetFound;
	vector<FrontField> lastFront;
	DistanceMatrix *distances = new DistanceMatrix(extents[m_grid->getHeight()][m_grid->getWidth()]);

	initializeDistances(*distances);
	calculateDistances(*distances, lastFront, startPosition, targetFound, canWalkOn, target);

#ifndef NDEBUG
	writeDebuggingInformationToFile(*distances);
#endif

	if (!targetFound)
		return Route(0, PlayerState::PlayerDirectionNone);

	GridPoint targetPosition = findTargetPositionInLastFront(lastFront, target);
	Route result = findWayBackToSourceFromTarget(*distances, targetPosition);
	delete distances;
	return result;
}

void Router::initializeDistances(DistanceMatrix &distances) const
{
	unsigned int height = m_grid->getHeight();
	unsigned int width = m_grid->getWidth();

	for (unsigned int x = 0; x < width; ++x)
		for (unsigned int y = 0; y < height; ++y)
			distances[y][x] = 0;
}

void Router::updateDistanceForPosition(DistanceMatrix &distances,
		vector<FrontField> &lastFront, unsigned int actualDistance,
		const GridPoint &previousPosition, const GridPoint &newPosition, bool &targetFound,
		const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target) const
{
	const RouterGridField &newField = m_grid->getField(newPosition);
	const RouterGridField &oldField = m_grid->getField(previousPosition);

	if (distances[newPosition.getY()][newPosition.getX()] == 0 && canWalkOn.decide(newField, oldField, true))
	{
		distances[newPosition.getY()][newPosition.getX()] = actualDistance;
		lastFront.push_back(FrontField(newPosition, previousPosition));
	}

	if (target.decide(newField, oldField, true))
	{
		distances[newPosition.getY()][newPosition.getX()] = actualDistance;
		lastFront.push_back(FrontField(newPosition, previousPosition));
		targetFound = true;
	}
}

void Router::calculateDistances(DistanceMatrix &distances, vector<FrontField> &lastFront,
		const GridPoint &startPosition, bool &targetFound,
		const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target) const
{
	lastFront.clear();
	lastFront.push_back(FrontField(startPosition, startPosition));
	distances[startPosition.getY()][startPosition.getX()] = 1;
	unsigned int distance = 1;
	targetFound = false;

	do
	{
		++distance;
		vector<FrontField> newLastFront;

		for (vector<FrontField>::const_iterator i = lastFront.begin(); i != lastFront.end(); ++i)
		{
			const GridPoint &oldPosition = i->first;
			unsigned int x = oldPosition.getX();
			unsigned int y = oldPosition.getY();

			if (x > 0)
			{
				GridPoint newPosition(x - 1, y);
				updateDistanceForPosition(distances, newLastFront, distance, oldPosition, newPosition, targetFound, canWalkOn, target);
			}

			if (y > 0)
			{
				GridPoint newPosition(x, y - 1);
				updateDistanceForPosition(distances, newLastFront, distance, oldPosition, newPosition, targetFound, canWalkOn, target);
			}

			if (x < m_grid->getWidth() - 1)
			{
				GridPoint newPosition(x + 1, y);
				updateDistanceForPosition(distances, newLastFront, distance, oldPosition, newPosition, targetFound, canWalkOn, target);
			}

			if (y < m_grid->getHeight() - 1)
			{
				GridPoint newPosition(x, y + 1);
				updateDistanceForPosition(distances, newLastFront, distance, oldPosition, newPosition, targetFound, canWalkOn, target);
			}
		}

		lastFront = newLastFront;
	} while (!targetFound && lastFront.size() > 0);
}

GridPoint Router::findTargetPositionInLastFront(const vector<FrontField> &lastFront,
												const RouterGridFieldDecider &target) const
{
	GridPoint targetPosition;
	bool targetFound = false;

	for (vector<FrontField>::const_iterator i = lastFront.begin(); i != lastFront.end() && !targetFound; ++i)
	{
		targetPosition = i->first;
		const RouterGridField &targetField = m_grid->getField(targetPosition);
		const RouterGridField &preTargetField = m_grid->getField(i->second);

		if (target.decide(targetField, preTargetField, true))
			targetFound = true;
	}

	assert(targetFound);

	return targetPosition;
}

Route Router::findWayBackToSourceFromTarget(DistanceMatrix &distances, const GridPoint &targetPosition) const
{
	PlayerState::PlayerDirection lastDirection = PlayerState::PlayerDirectionNone;
	unsigned int distanceToTarget = distances[targetPosition.getY()][targetPosition.getX()];
	unsigned int lastDistance = distanceToTarget;
	GridPoint position = targetPosition;
	GridPoint playersTargetPosition;

	while (lastDistance != 1)
	{
		bool foundSmallerDistance = false;

		if (position.getX() > 0)
		{
			unsigned int newDistance = distances[position.getY()][position.getX() - 1];
			if (newDistance == lastDistance - 1)
			{
				foundSmallerDistance = true;
				--lastDistance;
				lastDirection = PlayerState::PlayerDirectionRight;
				position.setX(position.getX() - 1);
			}
		}

		if (position.getY() > 0 && !foundSmallerDistance)
		{
			unsigned int newDistance = distances[position.getY() - 1][position.getX()];
			if (newDistance == lastDistance - 1)
			{
				foundSmallerDistance = true;
				--lastDistance;
				lastDirection = PlayerState::PlayerDirectionUp;
				position.setY(position.getY() - 1);
			}
		}

		if (position.getX() < m_grid->getWidth() - 1 && !foundSmallerDistance)
		{
			unsigned int newDistance = distances[position.getY()][position.getX() + 1];
			if (newDistance == lastDistance - 1)
			{
				foundSmallerDistance = true;
				--lastDistance;
				lastDirection = PlayerState::PlayerDirectionLeft;
				position.setX(position.getX() + 1);
			}
		}

		if (position.getY() < m_grid->getHeight() - 1 && !foundSmallerDistance)
		{
			unsigned int newDistance = distances[position.getY() + 1][position.getX()];
			if (newDistance == lastDistance - 1)
			{
				foundSmallerDistance = true;
				--lastDistance;
				lastDirection = PlayerState::PlayerDirectionDown;
				position.setY(position.getY() + 1);
			}
		}
		if (lastDistance == distanceToTarget-1)
			playersTargetPosition = position;
	}

	return Route(distanceToTarget - 1, lastDirection, playersTargetPosition);
}
