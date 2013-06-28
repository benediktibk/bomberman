#include "gameengine/router.h"
#include "gameengine/notdangerousandfreedecider.h"
#include "gameengine/coveredbyplayerdecider.h"
#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/coveredbypowerupdecider.h"
#include "gameengine/freedecider.h"
#include "gameengine/routergrid.h"
#include <fstream>
#include <assert.h>

using namespace GameEngine;
using namespace Common;
using namespace std;
using namespace boost;

Router::Router(Grid &grid, const GameState &gameState, unsigned int playerID) :
	m_grid(new RouterGrid(grid, gameState, playerID)),
	m_distances(new DistanceMatrix(extents[m_grid->getHeight()][m_grid->getWidth()]))
{ }

Router::~Router()
{
	delete m_distances;
	delete m_grid;
}

void Router::updatePlayerFields()
{
	m_grid->updatePlayerFlags();
}

Route Router::getRouteToPlayer(const Common::GridPoint &position)
{
	Route routeToCalculatedAim = getRoute(NotDangerousAndFreeDecider(), CoveredByPlayerDecider(), position);

	m_grid->addBombToCalculatedForPositionCheck(routeToCalculatedAim.getTargetPosition());
	Route flightPath = getRouteToNotDangerousField(routeToCalculatedAim.getTargetPosition());
	m_grid->removeBombToCalculatedForPositionCheck(routeToCalculatedAim.getTargetPosition());

	if (flightPath.getDirection() != PlayerState::PlayerDirectionNone)
		return routeToCalculatedAim;

	return Route(0, PlayerState::PlayerDirectionNone);

}

Route Router::getRouteToNotDangerousField(const Common::GridPoint &position)
{
	return getRoute(FreeDecider(), NotDangerousAndFreeDecider(), position);
}

Route Router::getRouteToLooseWall(const Common::GridPoint &position)
{
	Route routeToCalculatedAim = getRoute(NotDangerousAndFreeDecider(), CoveredByLooseWallDecider(), position);

	m_grid->addBombToCalculatedForPositionCheck(routeToCalculatedAim.getTargetPosition());
	Route flightPath = getRouteToNotDangerousField(routeToCalculatedAim.getTargetPosition());
	m_grid->removeBombToCalculatedForPositionCheck(routeToCalculatedAim.getTargetPosition());

	if (flightPath.getDirection() != PlayerState::PlayerDirectionNone)
		return routeToCalculatedAim;

	return Route(0, PlayerState::PlayerDirectionNone);
}

Route Router::getRouteToPowerUp(const GridPoint &position)
{
	return getRoute(NotDangerousAndFreeDecider(), CoveredByPowerUpDecider(), position);
}

void Router::writeDebuggingInformationToFile() const
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
			file << (*m_distances)[y][x] << ";";

		file << endl;
	}
}

Route Router::getRoute(const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target, const GridPoint &startPosition)
{
	if (target.decide(m_grid->getField(startPosition)))
		return Route(0, PlayerState::PlayerDirectionNone);

	bool targetFound;
	vector<GridPoint> lastFront;

	initializeDistances();
	calculateDistances(lastFront, startPosition, targetFound, canWalkOn, target);

#ifndef NDEBUG
	writeDebuggingInformationToFile();
#endif

	if (!targetFound)
		return Route(0, PlayerState::PlayerDirectionNone);

	GridPoint targetPosition = findTargetPositionInLastFront(lastFront, target);
	return findWayBackToSourceFromTarget(targetPosition);
}

void Router::initializeDistances()
{
	unsigned int height = m_grid->getHeight();
	unsigned int width = m_grid->getWidth();

	for (unsigned int x = 0; x < width; ++x)
		for (unsigned int y = 0; y < height; ++y)
			(*m_distances)[y][x] = 0;
}

void Router::updateDistanceForPosition(vector<GridPoint> &lastFront, unsigned int actualDistance,
		const GridPoint &position, bool &targetFound,
		const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target)
{
	const RouterGridField &newField = m_grid->getField(position);
	if ((*m_distances)[position.getY()][position.getX()] == 0 && canWalkOn.decide(newField))
	{
		(*m_distances)[position.getY()][position.getX()] = actualDistance;
		lastFront.push_back(position);
	}

	if (target.decide(newField))
	{
		(*m_distances)[position.getY()][position.getX()] = actualDistance;
		lastFront.push_back(position);
		targetFound = true;
	}
}

void Router::calculateDistances(std::vector<GridPoint> &lastFront,
		const GridPoint &startPosition, bool &targetFound,
		const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target)
{
	lastFront.clear();
	lastFront.push_back(startPosition);
	(*m_distances)[startPosition.getY()][startPosition.getX()] = 1;
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
				updateDistanceForPosition(newLastFront, distance, newPosition, targetFound, canWalkOn, target);
			}

			if (y > 0)
			{
				GridPoint newPosition(x, y - 1);
				updateDistanceForPosition(newLastFront, distance, newPosition, targetFound, canWalkOn, target);
			}

			if (x < m_grid->getWidth() - 1)
			{
				GridPoint newPosition(x + 1, y);
				updateDistanceForPosition(newLastFront, distance, newPosition, targetFound, canWalkOn, target);
			}

			if (y < m_grid->getHeight() - 1)
			{
				GridPoint newPosition(x, y + 1);
				updateDistanceForPosition(newLastFront, distance, newPosition, targetFound, canWalkOn, target);
			}
		}

		lastFront = newLastFront;
	} while (!targetFound && lastFront.size() > 0);
}

GridPoint Router::findTargetPositionInLastFront(const vector<GridPoint> &lastFront, const RouterGridFieldDecider &target) const
{
	GridPoint targetPosition;
	bool targetFound = false;

	for (vector<GridPoint>::const_iterator i = lastFront.begin(); i != lastFront.end() && !targetFound; ++i)
	{
		targetPosition = *i;
		const RouterGridField &targetField = m_grid->getField(targetPosition);

		if (target.decide(targetField))
			targetFound = true;
	}

	assert(targetFound);

	return targetPosition;
}

Route Router::findWayBackToSourceFromTarget(const GridPoint &targetPosition) const
{
	PlayerState::PlayerDirection lastDirection = PlayerState::PlayerDirectionNone;
	unsigned int distanceToTarget = (*m_distances)[targetPosition.getY()][targetPosition.getX()];
	unsigned int lastDistance = distanceToTarget;
	GridPoint position = targetPosition;
	GridPoint playersTargetPosition;

	while (lastDistance != 1)
	{
		bool foundSmallerDistance = false;

		if (position.getX() > 0)
		{
			unsigned int newDistance = (*m_distances)[position.getY()][position.getX() - 1];
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
			unsigned int newDistance = (*m_distances)[position.getY() - 1][position.getX()];
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
			unsigned int newDistance = (*m_distances)[position.getY()][position.getX() + 1];
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
			unsigned int newDistance = (*m_distances)[position.getY() + 1][position.getX()];
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
