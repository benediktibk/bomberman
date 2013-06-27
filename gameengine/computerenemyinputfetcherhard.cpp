#include "gameengine/computerenemyinputfetcherhard.h"
#include "gameengine/router.h"

using namespace GameEngine;
using namespace Common;

ComputerEnemyInputFetcherHard::ComputerEnemyInputFetcherHard(Common::Grid &grid, const Common::GameState &gameState, unsigned int playerID) :
	ComputerEnemyInputFetcher(grid, gameState, playerID)
{ }

void ComputerEnemyInputFetcherHard::calculateInputStateInternal()
{
	GridPoint playerPosition = getPlayerPosition();
	Router &router = getRouter();
	router.updatePlayerFields();

	Route routeToNotDangerousField = router.getRouteToNotDangerousField(playerPosition);
	if (routeToNotDangerousField.getDirection() != PlayerState::PlayerDirectionNone)
	{
		setInputStateIntoDirection(routeToNotDangerousField.getDirection());
		return;
	}

	Route routeToPowerUp = router.getRouteToPowerUp(playerPosition);
	if (routeToPowerUp.getDirection() != PlayerState::PlayerDirectionNone)
	{
		setInputStateIntoDirection(routeToPowerUp.getDirection());
		return;
	}

	Route routeToPlayer = router.getRouteToPlayer(playerPosition);
	if (routeToPlayer.getDirection() != PlayerState::PlayerDirectionNone)
	{
		placeBombIfCloseEnough(routeToPlayer);
		return;
	}

	Route routeToLooseWall = router.getRouteToLooseWall(playerPosition);
	if (routeToLooseWall.getDirection() != PlayerState::PlayerDirectionNone)
	{
		placeBombIfCloseEnough(routeToLooseWall);
		return;
	}
}
