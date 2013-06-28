#ifndef GAMEENGINE_ROUTER_H
#define GAMEENGINE_ROUTER_H

#include "gameengine/route.h"
#include "gameengine/routergridfielddecider.h"
#include "common/gridpoint.h"
#include <boost/multi_array.hpp>

namespace Common
{
	class GameState;
	class Grid;
}

namespace GameEngine
{
	class RouterGrid;

	class Router
	{
	private:
		typedef boost::multi_array<unsigned int, 2> DistanceMatrix;

	public:
		Router(Common::Grid &grid, const Common::GameState &gameState, unsigned int playerID);
		~Router();

		void updatePlayerFields();
		Route getRouteToPlayer(const Common::GridPoint &position);
		Route getRouteToNotDangerousField(const Common::GridPoint &position);
		Route getRouteToLooseWall(const Common::GridPoint &position);
		Route getRouteToPowerUp(const Common::GridPoint &position);

	private:
		void writeDebuggingInformationToFile() const;

	private:
		Route getRoute(
				const RouterGridFieldDecider &canWalkOn,
				const RouterGridFieldDecider &target,
				const Common::GridPoint &startPosition);
		void initializeDistances();
		void updateDistanceForPosition(
				std::vector<Common::GridPoint> &lastFront, unsigned int actualDistance,
				const Common::GridPoint &position, bool &targetFound,
				const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target);
		void calculateDistances(
				std::vector<Common::GridPoint> &lastFront,
				const Common::GridPoint &startPosition, bool &targetFound,
				const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target);
		Common::GridPoint findTargetPositionInLastFront(
				const std::vector<Common::GridPoint> &lastFront, const RouterGridFieldDecider &target) const;
		Route findWayBackToSourceFromTarget(const Common::GridPoint &targetPosition) const;
		bool isFlightableBombPlace(const Common::GridPoint &bombPlace);

	private:
		RouterGrid *m_grid;
		DistanceMatrix *m_distances;
	};
}

#endif
