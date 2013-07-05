#include "gameengine/computerenemyinputfetchermedium.h"
#include "gameengine/router.h"
#include "common/randomdecision.h"

using namespace GameEngine;
using namespace Common;

ComputerEnemyInputFetcherMedium::ComputerEnemyInputFetcherMedium(Common::Grid &grid, const Common::GameState &gameState) :
	ComputerEnemyInputFetcher(grid, gameState),
	m_getAwayFromDangerousField(new RandomDecision(0.5)),
	m_doSomething(new RandomDecision(0.1))
{ }

ComputerEnemyInputFetcherMedium::~ComputerEnemyInputFetcherMedium()
{
	delete m_getAwayFromDangerousField;
	delete m_doSomething;
}

void ComputerEnemyInputFetcherMedium::calculateInputStateInternal()
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

	Route routeToPlayer = router.getRouteToPlayer(playerPosition, getDestructionRangeOfNewBombs(), getPlayerSpeed(), getBombLifeTime(), false);
	Route routeToLooseWall = router.getRouteToLooseWall(playerPosition, getDestructionRangeOfNewBombs(), getPlayerSpeed(), getBombLifeTime(), false);

	bool wallIsMuchCloser = (routeToPlayer.getDistance() > 5*routeToLooseWall.getDistance()) && (routeToLooseWall.getDirection() != PlayerState::PlayerDirectionNone);

	if ((routeToPlayer.getDirection() != PlayerState::PlayerDirectionNone) && !wallIsMuchCloser)
	{
		placeBombIfCloseEnough(routeToPlayer);
		return;
	}

	if (routeToLooseWall.getDirection() != PlayerState::PlayerDirectionNone)
	{
		placeBombIfCloseEnough(routeToLooseWall);
		return;
	}
}
