#include "gameengineimpl.h"

using namespace GameEngine;
using namespace Common;

void GameEngineImpl::updateGameState(const InputState &inputState)
{
	double timeUnit = m_stopWatch.getTimeAndRestart();
	if (timeUnit == 0)
		return;

	m_inputState = inputState;

	if(m_inputState.isUpKeyPressed())
	{
		double additionalPosition = 10*timeUnit;
		PlayerState playerState = m_gameState.getPlayerState();
		double oldPosition = playerState.getPosition();
		playerState.setPosition(oldPosition + additionalPosition);
		m_gameState.setPlayerState(playerState);
	}
}

void GameEngineImpl::resetTime()
{
	m_stopWatch.restart();
}

const Common::GameState &GameEngineImpl::getGameState()
{
	return m_gameState;
}