#include "common/gameenginestub.h"

using namespace Common;
using namespace std;

GameEngineStub::GameEngineStub() :
	m_state(m_level, 1, m_idCreator, m_idCreator),
	m_grid(1, 1)
{ }

void GameEngineStub::updateGameState(const map<unsigned int, InputState> &, double)
{ }

const GameState &GameEngineStub::getGameState() const
{
	return m_state;
}

Grid &GameEngineStub::getGrid()
{
	return m_grid;
}

vector<unsigned int> GameEngineStub::getAllPossiblePlayerIDs() const
{
	 vector<unsigned int> result;
	 result.push_back(23);
	 return result;
}
