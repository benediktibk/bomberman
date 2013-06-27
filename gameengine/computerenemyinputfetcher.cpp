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
	m_playerID(playerID),
	m_player(gameState.getPlayerStateById(playerID))
{
	m_inputStateWithID.insert(pair<unsigned int, InputState>(m_playerID, m_inputState));
}

ComputerEnemyInputFetcher::~ComputerEnemyInputFetcher()
{
	delete m_router;
}

InputState ComputerEnemyInputFetcher::getInputState()
{
	calculateInputState();
	return m_inputState;
}

void ComputerEnemyInputFetcher::calculateInputState()
{
	m_inputState.setDownKeyNotPressed();
	m_inputState.setUpKeyNotPressed();
	m_inputState.setRightKeyNotPressed();
	m_inputState.setLeftKeyNotPressed();
	m_inputState.setSpaceKeyNotPressed();

	if (!m_gameState.isPlayerAlive(m_playerID))
		return;

	calculateInputStateInternal();
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

void ComputerEnemyInputFetcher::placeBombIfCloseEnough(const Route &route)
{
	Point realPosition = m_player.getPosition();
	GridPoint targetPosition = Grid::getTargetPoint(m_player);
	Point positionToTargetDifference = realPosition - targetPosition.getPointPosition();
	bool closeEnoughForBombPlacement =	route.getDistance() <= 1 &&
										abs(positionToTargetDifference.getX()) < 0.45 &&
										abs(positionToTargetDifference.getY()) < 0.45;

	if (closeEnoughForBombPlacement)
		m_inputState.setSpaceKeyPressed();
	else if (route.getDistance() > 1)
		setInputStateIntoDirection(route.getDirection());
}

map<unsigned int, InputState> ComputerEnemyInputFetcher::getInputStates()
{
	calculateInputState();
	m_inputStateWithID[m_playerID] = m_inputState;
	return m_inputStateWithID;
}


Router& GameEngine::ComputerEnemyInputFetcher::getRouter()
{
	return *m_router;
}

GridPoint ComputerEnemyInputFetcher::getPlayerPosition() const
{
	return Grid::getTargetPoint(m_player);
}

unsigned int ComputerEnemyInputFetcher::getPlayerID()
{
    return m_playerID;
}
