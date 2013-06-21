#ifndef GAMEENGINE_ROUTER_H
#define GAMEENGINE_ROUTER_H

#include "gameengine/route.h"
#include "common/gridpoint.h"

namespace GameEngine
{
	class Router
	{
	public:
		Router();

		Route getRouteToPlayer(const Common::GridPoint &position) const;
		Route getRouteToNotDangerousField(const Common::GridPoint &position) const;
		Route getRouteToLooseWall(const Common::GridPoint &position) const;
	};
}

#endif
