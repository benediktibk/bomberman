#include "gameengineimpl.h"

using namespace GameEngine;
using namespace Common;

void GameEngineImpl::updateGameState(const InputState &inputState)
{
	m_inputState = inputState;

	if(m_inputState.isUpKeyPressed())
	{
		double additionalPosition = 5;
		PlayerState playerState = m_gameState.getPlayerState();
		double oldPosition = playerState.getPosition();
		playerState.setPosition(oldPosition + additionalPosition);
		m_gameState.setPlayerState(playerState);
	}
}

const Common::GameState &GameEngineImpl::getGameState()
{
	return m_gameState;
}