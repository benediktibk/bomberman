#include "common/gameenginemock.h"

using namespace Common;
using namespace std;

GameEngineMock::GameEngineMock() :
	m_state(m_level, 1, m_idCreator, m_idCreator),
	m_grid(1, 1),
	m_callsToUpdateGameState(0)
{ }

void GameEngineMock::updateGameState(const map<unsigned int, InputState> &, double)
{
	++m_callsToUpdateGameState;
}

const GameState &GameEngineMock::getGameState() const
{
	return m_state;
}

Grid &GameEngineMock::getGrid()
{
	return m_grid;
}

vector<unsigned int> GameEngineMock::getAllPossiblePlayerIDs() const
{
	return m_state.getAllPossiblePlayerIDs();
}

unsigned int GameEngineMock::getCallsToUpdateGameState() const
{
	return m_callsToUpdateGameState;
}
