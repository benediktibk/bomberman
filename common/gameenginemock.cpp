#include "common/gameenginemock.h"

using namespace Common;

GameEngineMock::GameEngineMock() :
	m_state(m_level, 1, m_idCreator, m_idCreator),
	m_callsToUpdateGameState(0)
{ }

void GameEngineMock::updateGameState(const InputState &, double)
{
	++m_callsToUpdateGameState;
}

const GameState &GameEngineMock::getGameState() const
{
	return m_state;
}

unsigned int GameEngineMock::getCallsToUpdateGameState() const
{
	return m_callsToUpdateGameState;
}
