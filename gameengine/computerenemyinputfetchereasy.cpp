#include "gameengine/computerenemyinputfetchereasy.h"
#include "gameengine/router.h"
#include "common/randomdecision.h"

using namespace GameEngine;
using namespace Common;

ComputerEnemyInputFetcherEasy::ComputerEnemyInputFetcherEasy(Common::Grid &grid, const Common::GameState &gameState) :
	ComputerEnemyInputFetcher(grid, gameState),
	m_getAwayFromDangerousField(new RandomDecision(0.3)),
	m_doSomething(new RandomDecision(0.1))
{ }

ComputerEnemyInputFetcherEasy::~ComputerEnemyInputFetcherEasy()
{
	delete m_getAwayFromDangerousField;
	delete m_doSomething;
}

void ComputerEnemyInputFetcherEasy::calculateInputStateInternal()
{
	GridPoint playerPosition = getPlayerPosition();
	Router &router = getRouter();
	router.updatePlayerFields();

	Route routeToNotDangerousField = router.getRouteToNotDangerousField(playerPosition);
	if (routeToNotDangerousField.getDirection() != PlayerState::PlayerDirectionNone && m_getAwayFromDangerousField->decide())
	{
		setInputStateIntoDirection(routeToNotDangerousField.getDirection());
		return;
	}

	if (!m_doSomething->decide())
		return;

	Route routeToLooseWall = router.getRouteToLooseWall(playerPosition, getDestructionRangeOfNewBombs(), false);
	if (routeToLooseWall.getDirection() != PlayerState::PlayerDirectionNone)
	{
		placeBombIfCloseEnough(routeToLooseWall);
		return;
	}

	Route routeToPlayer = router.getRouteToPlayer(playerPosition);
	if (routeToPlayer.getDirection() != PlayerState::PlayerDirectionNone)
	{
		placeBombIfCloseEnough(routeToPlayer);
		return;
	}
}
