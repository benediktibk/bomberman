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
		//! first element: actual position, second element: previous position
		typedef std::pair<Common::GridPoint, Common::GridPoint> FrontField;

	public:
		Router(Common::Grid &grid, const Common::GameState &gameState, unsigned int playerID);
		~Router();

		void updatePlayerFields();
		Route getRouteToPlayer(const Common::GridPoint &position) const;
		Route getRouteToNotDangerousField(const Common::GridPoint &position) const;
		Route getRouteToLooseWall(const Common::GridPoint &position, unsigned int bombRange, bool considerEscape) const;
		Route getRouteToPowerUp(const Common::GridPoint &position) const;
		bool canEscapeFromIfBombPlaced(const Common::GridPoint &position, unsigned int bombRange) const;

	private:
		void writeDebuggingInformationToFile(DistanceMatrix &distances) const;

	private:
		Route getRoute(
				const RouterGridFieldDecider &canWalkOn,
				const RouterGridFieldDecider &target,
				const Common::GridPoint &startPosition) const;
		void initializeDistances(DistanceMatrix &distances) const;
		void updateDistanceForPosition(DistanceMatrix &distances, std::vector<FrontField> &lastFront, unsigned int actualDistance,
				const Common::GridPoint &previousPosition, const Common::GridPoint &newPosition, bool &targetFound,
				const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target) const;
		void calculateDistances(DistanceMatrix &distances,
				std::vector<FrontField> &lastFront,
				const Common::GridPoint &startPosition, bool &targetFound,
				const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target) const;
		Common::GridPoint findTargetPositionInLastFront(
				const std::vector<FrontField> &lastFront, const RouterGridFieldDecider &target) const;
		Route findWayBackToSourceFromTarget(DistanceMatrix &distances, const Common::GridPoint &targetPosition) const;

	private:
		RouterGrid *m_grid;
	};
}

#endif
