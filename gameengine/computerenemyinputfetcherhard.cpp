#include "gameengine/computerenemyinputfetcherhard.h"
#include "gameengine/router.h"

using namespace GameEngine;
using namespace Common;

ComputerEnemyInputFetcherHard::ComputerEnemyInputFetcherHard(Common::Grid &grid, const Common::GameState &gameState) :
	ComputerEnemyInputFetcher(grid, gameState)
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
	Route routeToPlayer = router.getRouteToPlayer(playerPosition, getDestructionRangeOfNewBombs(), getPlayerSpeed(), getBombLifeTime(), true);

	bool playerIsMuchCloser = (routeToPowerUp.getDistance() > 2*routeToPlayer.getDistance()) && (routeToPlayer.getDirection() != PlayerState::PlayerDirectionNone);

	if ((routeToPowerUp.getDirection() != PlayerState::PlayerDirectionNone) && !playerIsMuchCloser)
	{
		setInputStateIntoDirection(routeToPowerUp.getDirection());
		return;
	}

	if (routeToPlayer.getDirection() != PlayerState::PlayerDirectionNone)
	{
		placeBombIfCloseEnough(routeToPlayer);
		return;
	}

	Route routeToLooseWall = router.getRouteToLooseWall(playerPosition, getDestructionRangeOfNewBombs(), getPlayerSpeed(), getBombLifeTime(), true);
	if (routeToLooseWall.getDirection() != PlayerState::PlayerDirectionNone)
	{
		placeBombIfCloseEnough(routeToLooseWall);
		return;
	}
}
