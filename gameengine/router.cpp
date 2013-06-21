#include "gameengine/router.h"
#include "gameengine/notdangerousandfreedecider.h"
#include "gameengine/coveredbyplayerdecider.h"
#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/freedecider.h"
#include "gameengine/routergrid.h"
#include <boost/multi_array.hpp>

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

Route Router::getRoute(const RouterGridFieldDecider &/*canWalkOn*/, const RouterGridFieldDecider &target, const GridPoint &startPosition) const
{
	typedef multi_array<unsigned int, 2> DistanceMatrix;
	unsigned int height = m_grid->getHeight();
	unsigned int width = m_grid->getWidth();
	DistanceMatrix distances(extents[height][width]);
	vector<GridPoint> lastFront;

	for (unsigned int x = 0; x < width; ++x)
		for (unsigned int y = 0; y < height; ++y)
			distances[y][x] = 0;

	lastFront.push_back(startPosition);
	bool targetReached = false;
	Route result(0, PlayerState::PlayerDirectionNone);

	do
	{

		for (vector<GridPoint>::const_iterator i = lastFront.begin(); i != lastFront.end() && !targetReached; ++i)
		{
			GridPoint targetPosition = *i;
			const RouterGridField &field = m_grid->getField(targetPosition);
			if (target.decide(field))
			{
				targetReached = true;
				PlayerState::PlayerDirection lastDirection;
				unsigned int distance = distances[targetPosition.getY()][targetPosition.getX()];
				unsigned int lastDistance = distance;
				GridPoint position = targetPosition;

				while (lastDistance != 1)
				{
					bool foundSmallerDistance = false;

					if (position.getX() > 0)
					{
						if (distances[position.getY()][position.getX() - 1] == lastDistance - 1)
						{
							foundSmallerDistance = true;
							--lastDistance;
							position.setX(position.getX() - 1);
						}
					}

					if (position.getX() > 0 && !foundSmallerDistance)
					{
						if (distances[position.getY() - 1][position.getX()] == lastDistance - 1)
						{
							foundSmallerDistance = true;
							--lastDistance;
							position.setY(position.getY() - 1);
						}
					}

					if (position.getX() < m_grid->getWidth() - 1 && !foundSmallerDistance)
					{
						if (distances[position.getY()][position.getX() + 1] == lastDistance - 1)
						{
							foundSmallerDistance = true;
							--lastDistance;
							position.setX(position.getX() + 1);
						}
					}

					if (position.getY() < m_grid->getHeight() - 1 && !foundSmallerDistance)
					{
						if (distances[position.getY() + 1][position.getX()] == lastDistance - 1)
						{
							foundSmallerDistance = true;
							--lastDistance;
							position.setX(position.getX() + 1);
						}
					}
				}

				result = Route(distance - 1, lastDirection);
			}
		}

	} while (!targetReached);

	return result;
}
