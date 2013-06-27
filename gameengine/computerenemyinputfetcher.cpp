#include "gameengine/computerenemyinputfetcher.h"
#include "gameengine/router.h"
#include "common/grid.h"
#include "common/gamestate.h"

using namespace Common;
using namespace GameEngine;
using namespace std;

ComputerEnemyInputFetcher::ComputerEnemyInputFetcher(Grid &grid, const GameState &gameState, unsigned int playerID) :
	m_router(new Router(grid, gameState, playerID)),
	m_gameState(gameState),
	m_playerID(playerID)
{ }

ComputerEnemyInputFetcher::~ComputerEnemyInputFetcher()
{
	delete m_router;
}

InputState ComputerEnemyInputFetcher::getInputState()
{
	m_inputState.setSpaceKeyNotPressed();

	if (!m_gameState.isPlayerAlive(m_playerID))
		return m_inputState;

	const PlayerState &player = m_gameState.getPlayerStateById(m_playerID);
	GridPoint playerPosition = Grid::getTargetPoint(player);
	m_router->updatePlayerFields();

	Route routeToNotDangerousField = m_router->getRouteToNotDangerousField(playerPosition);
	if (routeToNotDangerousField.getDirection() != PlayerState::PlayerDirectionNone)
	{
		setInputStateIntoDirection(routeToNotDangerousField.getDirection());
		return m_inputState;
	}

	Route routeToPowerUp = m_router->getRouteToPowerUp(playerPosition);
	if (routeToPowerUp.getDirection() != PlayerState::PlayerDirectionNone)
	{
		setInputStateIntoDirection(routeToPowerUp.getDirection());
		return m_inputState;
	}

	Route routeToPlayer = m_router->getRouteToPlayer(playerPosition);
	if (routeToPlayer.getDirection() != PlayerState::PlayerDirectionNone)
	{
		Point realPosition = player.getPosition();
		Point positionToTargetDifference = realPosition - playerPosition.getPointPosition();
		bool closeEnoughForBombPlacement =	routeToPlayer.getDistance() <= 1 &&
											abs(positionToTargetDifference.getX()) < 0.45 &&
											abs(positionToTargetDifference.getY()) < 0.45;

		if (closeEnoughForBombPlacement)
		{
			m_inputState.setSpaceKeyPressed();
			return m_inputState;
		}
		else if (routeToPlayer.getDistance() == 1)
		{
			setInputStateIntoDirection(PlayerState::PlayerDirectionNone);
			return m_inputState;
		}
		else
		{
			setInputStateIntoDirection(routeToPlayer.getDirection());
			return m_inputState;
		}
	}

	Route routeToLooseWall = m_router->getRouteToLooseWall(playerPosition);
	if (routeToLooseWall.getDirection() != PlayerState::PlayerDirectionNone)
	{
		Point realPosition = player.getPosition();
		Point positionToTargetDifference = realPosition - playerPosition.getPointPosition();
		bool closeEnoughForBombPlacement =	routeToLooseWall.getDistance() <= 1 &&
											abs(positionToTargetDifference.getX()) < 0.45 &&
											abs(positionToTargetDifference.getY()) < 0.45;

		if (closeEnoughForBombPlacement)
		{
			m_inputState.setSpaceKeyPressed();
			return m_inputState;
		}
		else if (routeToLooseWall.getDistance() == 1)
		{
			setInputStateIntoDirection(PlayerState::PlayerDirectionNone);
			return m_inputState;
		}
		else
		{
			setInputStateIntoDirection(routeToLooseWall.getDirection());
			return m_inputState;
		}
	}

	setInputStateIntoDirection(PlayerState::PlayerDirectionNone);
	return m_inputState;
}

void ComputerEnemyInputFetcher::setInputStateIntoDirection(PlayerState::PlayerDirection direction)
{
	m_inputState.setDownKeyNotPressed();
	m_inputState.setRightKeyNotPressed();
	m_inputState.setLeftKeyNotPressed();
	m_inputState.setUpKeyNotPressed();

	switch(direction)
	{
	case PlayerState::PlayerDirectionLeft:
		m_inputState.setLeftKeyPressed();
		break;
	case PlayerState::PlayerDirectionUp:
		m_inputState.setUpKeyPressed();
		break;
	case PlayerState::PlayerDirectionRight:
		m_inputState.setRightKeyPressed();
		break;
	case PlayerState::PlayerDirectionDown:
		m_inputState.setDownKeyPressed();
		break;
	case PlayerState::PlayerDirectionNone:
		break;
	}
}

std::map<unsigned int, InputState> ComputerEnemyInputFetcher::getInputStates()
{
	std::map<unsigned int, InputState> result;
	return result;
}
