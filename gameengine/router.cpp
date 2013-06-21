#include "gameengine/router.h"
#include "gameengine/notdangerousandfreedecider.h"
#include "gameengine/coveredbyplayerdecider.h"
#include "gameengine/coveredbyloosewalldecider.h"

using namespace GameEngine;

Router::Router()
{
}

Route Router::getRouteToPlayer(const Common::GridPoint &/*position*/) const
{
	return getRoute(NotDangerousAndFreeDecider(), CoveredByPlayerDecider());
}

Route Router::getRouteToNotDangerousField(const Common::GridPoint &/*position*/) const
{
	return getRoute(, NotDangerousAndFreeDecider());
}

Route Router::getRouteToLooseWall(const Common::GridPoint &/*position*/) const
{
	return getRoute(NotDangerousAndFreeDecider(), CoveredByLooseWallDecider());
}

Route Router::getRoute(const RouterGridFieldDecider &/*canWalkOn*/, const RouterGridFieldDecider &/*target*/) const
{
	return Route();
}
