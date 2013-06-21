#ifndef GAMEENGINE_ROUTER_H
#define GAMEENGINE_ROUTER_H

#include "gameengine/route.h"
#include "gameengine/routergridfielddecider.h"
#include "common/gridpoint.h"

namespace Common
{
	class GameState;
}

namespace GameEngine
{
	class Grid;
	class RouterGrid;

	class Router
	{
	public:
		Router(Grid &grid, const Common::GameState &gameState);
		~Router();

		Route getRouteToPlayer(const Common::GridPoint &position) const;
		Route getRouteToNotDangerousField(const Common::GridPoint &position) const;
		Route getRouteToLooseWall(const Common::GridPoint &position) const;

	private:
		Route getRoute(const RouterGridFieldDecider &canWalkOn, const RouterGridFieldDecider &target) const;

	private:
		RouterGrid *m_grid;
	};
}

#endif
