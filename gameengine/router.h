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
		Route getRouteToPlayer(const Common::GridPoint &position) const;
		Route getRouteToNotDangerousField(const Common::GridPoint &position) const;
		Route getRouteToLooseWall(const Common::GridPoint &position) const;

	private:
		static void writeDebuggingInformationToFile(const DistanceMatrix &distances, unsigned int width, unsigned int height);

	private:
		Route getRoute(
				const RouterGridFieldDecider &canWalkOn,
				const RouterGridFieldDecider &target,
				const Common::GridPoint &startPosition) const;
		void updateDistanceForPosition(
				DistanceMatrix &distances, std::vector<Common::GridPoint> &lastFront, unsigned int actualDistance,
				const Common::GridPoint &position, bool &targetFound,
				const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target) const;
		void calculateDistances(
				DistanceMatrix &distances, std::vector<Common::GridPoint> &lastFront,
				const Common::GridPoint &startPosition, bool &targetFound,
				const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target) const;

	private:
		RouterGrid *m_grid;
	};
}

#endif
