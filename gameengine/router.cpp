#include "gameengine/router.h"
#include "gameengine/notdangerousandfreedecider.h"
#include "gameengine/coveredbyplayerdecider.h"
#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/freedecider.h"
#include "gameengine/routergrid.h"
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

void Router::writeDebuggingInformationToFile(const Router::DistanceMatrix &distances, unsigned int width, unsigned int height)
{
	string fileName = "/var/tmp/ultimatebomberman_distances.csv";
	fstream file(fileName.c_str(), ios_base::out);

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

Route Router::getRoute(const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target, const GridPoint &startPosition) const
{
	unsigned int height = m_grid->getHeight();
	unsigned int width = m_grid->getWidth();
	DistanceMatrix distances(extents[height][width]);
	vector<GridPoint> lastFront;
	const RouterGridField &startField = m_grid->getField(startPosition);

	if (target.decide(startField))
		return Route(0, PlayerState::PlayerDirectionNone);

	for (unsigned int x = 0; x < width; ++x)
		for (unsigned int y = 0; y < height; ++y)
			distances[y][x] = 0;

	Route result(0, PlayerState::PlayerDirectionNone);
	bool targetFound = false;
	calculateDistances(distances, lastFront, startPosition, targetFound, canWalkOn, target);

	if (!targetFound)
		return result;

	GridPoint targetPosition;
	targetFound = false;

#ifndef NDEBUG
	writeDebuggingInformationToFile(distances, m_grid->getWidth(), m_grid->getHeight());
#endif

	for (vector<GridPoint>::const_iterator i = lastFront.begin(); i != lastFront.end() && !targetFound; ++i)
	{
		targetPosition = *i;
		const RouterGridField &targetField = m_grid->getField(targetPosition);

		if (target.decide(targetField))
			targetFound = true;
	}

	assert(targetFound);

	PlayerState::PlayerDirection lastDirection = PlayerState::PlayerDirectionNone;
	unsigned int distanceToTarget = distances[targetPosition.getY()][targetPosition.getX()];
	unsigned int lastDistance = distanceToTarget;
	GridPoint position = targetPosition;

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
	}

	result = Route(distanceToTarget - 1, lastDirection);

	return result;
}

void Router::updateDistanceForPosition(
		Router::DistanceMatrix &distances, vector<GridPoint> &lastFront, unsigned int actualDistance,
		const GridPoint &position, bool &targetFound,
		const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target) const
{
	const RouterGridField &newField = m_grid->getField(position);
	if (distances[position.getY()][position.getX()] == 0 && canWalkOn.decide(newField))
	{
		distances[position.getY()][position.getX()] = actualDistance;
		lastFront.push_back(position);
	}

	if (target.decide(newField))
	{
		distances[position.getY()][position.getX()] = actualDistance;
		lastFront.push_back(position);
		targetFound = true;
	}
}

void Router::calculateDistances(
		Router::DistanceMatrix &distances, std::vector<GridPoint> &lastFront,
		const GridPoint &startPosition, bool &targetFound,
		const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target) const
{
	lastFront.clear();
	lastFront.push_back(startPosition);
	distances[startPosition.getY()][startPosition.getX()] = 1;
	unsigned int distance = 1;
	targetFound = false;

	do
	{
		++distance;
		vector<GridPoint> newLastFront;

		for (vector<GridPoint>::const_iterator i = lastFront.begin(); i != lastFront.end(); ++i)
		{
			const GridPoint &position = *i;
			unsigned int x = position.getX();
			unsigned int y = position.getY();

			if (x > 0)
			{
				GridPoint newPosition(x - 1, y);
				updateDistanceForPosition(distances, newLastFront, distance, newPosition, targetFound, canWalkOn, target);
			}

			if (y > 0)
			{
				GridPoint newPosition(x, y - 1);
				updateDistanceForPosition(distances, newLastFront, distance, newPosition, targetFound, canWalkOn, target);
			}

			if (x < m_grid->getWidth() - 1)
			{
				GridPoint newPosition(x + 1, y);
				updateDistanceForPosition(distances, newLastFront, distance, newPosition, targetFound, canWalkOn, target);
			}

			if (y < m_grid->getHeight() - 1)
			{
				GridPoint newPosition(x, y + 1);
				updateDistanceForPosition(distances, newLastFront, distance, newPosition, targetFound, canWalkOn, target);
			}
		}

		lastFront = newLastFront;
	} while (!targetFound && lastFront.size() > 0);
}
