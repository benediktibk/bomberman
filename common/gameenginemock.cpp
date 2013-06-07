#include "common/gameenginemock.h"

using namespace Common;
using namespace std;

GameEngineMock::GameEngineMock() :
	m_state(m_level, 1, m_idCreator, m_idCreator),
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

vector<unsigned int> GameEngineMock::getAllPossiblePlayerIDs() const
{
	return vector<unsigned int>();
}

unsigned int GameEngineMock::getCallsToUpdateGameState() const
{
	return m_callsToUpdateGameState;
}
