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

	lastFront.push_back(startPosition);
	distances[startPosition.getY()][startPosition.getX()] = 1;
	Route result(0, PlayerState::PlayerDirectionNone);
	bool targetFound = false;
	unsigned int distance = 1;

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
				const RouterGridField &newField = m_grid->getField(newPosition);
				if (distances[newPosition.getY()][newPosition.getX()] == 0 && canWalkOn.decide(newField))
				{
					distances[newPosition.getY()][newPosition.getX()] = distance;
					newLastFront.push_back(newPosition);
				}

				if (target.decide(newField))
				{
					distances[newPosition.getY()][newPosition.getX()] = distance;
					newLastFront.push_back(newPosition);
					targetFound = true;
				}
			}

			if (y > 0)
			{
				GridPoint newPosition(x, y - 1);
				const RouterGridField &newField = m_grid->getField(newPosition);
				if (distances[newPosition.getY()][newPosition.getX()] == 0 && canWalkOn.decide(newField))
				{
					distances[newPosition.getY()][newPosition.getX()] = distance;
					newLastFront.push_back(newPosition);
				}

				if (target.decide(newField))
				{
					distances[newPosition.getY()][newPosition.getX()] = distance;
					newLastFront.push_back(newPosition);
					targetFound = true;
				}
			}

			if (x < m_grid->getWidth() - 1)
			{
				GridPoint newPosition(x + 1, y);
				const RouterGridField &newField = m_grid->getField(newPosition);
				if (distances[newPosition.getY()][newPosition.getX()] == 0 && canWalkOn.decide(newField))
				{
					distances[newPosition.getY()][newPosition.getX()] = distance;
					newLastFront.push_back(newPosition);
				}

				if (target.decide(newField))
				{
					distances[newPosition.getY()][newPosition.getX()] = distance;
					newLastFront.push_back(newPosition);
					targetFound = true;
				}
			}

			if (y < m_grid->getHeight() - 1)
			{
				GridPoint newPosition(x, y + 1);
				const RouterGridField &newField = m_grid->getField(newPosition);
				if (distances[newPosition.getY()][newPosition.getX()] == 0 && canWalkOn.decide(newField))
				{
					distances[newPosition.getY()][newPosition.getX()] = distance;
					newLastFront.push_back(newPosition);
				}

				if (target.decide(newField))
				{
					distances[newPosition.getY()][newPosition.getX()] = distance;
					newLastFront.push_back(newPosition);
					targetFound = true;
				}
			}
		}

		lastFront = newLastFront;
	} while (!targetFound && lastFront.size() > 0);

	if (!targetFound)
		return result;

	GridPoint targetPosition;
	targetFound = false;

//#ifdef NDEBUG
	writeDebuggingInformationToFile(distances, m_grid->getWidth(), m_grid->getHeight());
//#endif

	for (vector<GridPoint>::const_iterator i = lastFront.begin(); i != lastFront.end() && !targetFound; ++i)
	{
		targetPosition = *i;
		const RouterGridField &targetField = m_grid->getField(targetPosition);

		if (target.decide(targetField))
			targetFound = true;
	}

	assert(targetFound);

	PlayerState::PlayerDirection lastDirection;
	distance = distances[targetPosition.getY()][targetPosition.getX()];
	unsigned int lastDistance = distance;
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

	result = Route(distance - 1, lastDirection);

	return result;
}