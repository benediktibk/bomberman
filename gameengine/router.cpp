#include "gameengine/router.h"
#include "gameengine/notdangerousandfreedecider.h"
#include "gameengine/coveredbyplayerdecider.h"
#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/freedecider.h"
#include "gameengine/routergrid.h"

using namespace GameEngine;
using namespace Common;

Router::Router(Grid &grid, const GameState &gameState) :
	m_grid(new RouterGrid(grid, gameState))
{ }

Router::~Router()
{
	delete m_grid;
}

Route Router::getRouteToPlayer(const Common::GridPoint &/*position*/) const
{
	return getRoute(NotDangerousAndFreeDecider(), CoveredByPlayerDecider());
}

Route Router::getRouteToNotDangerousField(const Common::GridPoint &/*position*/) const
{
	return getRoute(FreeDecider(), NotDangerousAndFreeDecider());
}

Route Router::getRouteToLooseWall(const Common::GridPoint &/*position*/) const
{
	return getRoute(NotDangerousAndFreeDecider(), CoveredByLooseWallDecider());
}

Route Router::getRoute(const RouterGridFieldDecider &/*canWalkOn*/, const RouterGridFieldDecider &/*target*/) const
{
	return Route(0, PlayerState::PlayerDirectionDown);
}
