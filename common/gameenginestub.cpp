#include "common/gameenginestub.h"

using namespace Common;

GameEngineStub::GameEngineStub() :
	m_state(m_level, m_idCreator, m_idCreator)
{ }

void GameEngineStub::updateGameState(const InputState &, double)
{ }

const GameState &GameEngineStub::getGameState() const
{
	return m_state;
}
