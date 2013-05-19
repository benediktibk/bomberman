#include "gameengineimpl.h"

using namespace GameEngine;

void GameEngineImpl::updateGameState(const Common::InputState &inputState)
{
	m_inputState = inputState;
}

const Common::GameState &GameEngineImpl::getGameState()
{
	return m_gameState;
}