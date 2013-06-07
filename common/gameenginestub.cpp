#include "common/gameenginestub.h"

using namespace Common;
using namespace std;

GameEngineStub::GameEngineStub() :
	m_state(m_level, 1, m_idCreator, m_idCreator)
{ }

void GameEngineStub::updateGameState(const map<unsigned int, InputState> &, double)
{ }

const GameState &GameEngineStub::getGameState() const
{
	return m_state;
}

vector<unsigned int> GameEngineStub::getAllPossiblePlayerIDs() const
{
	return vector<unsigned int>();
}
