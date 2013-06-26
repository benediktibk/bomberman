#include "common/gameenginemock.h"

using namespace Common;
using namespace std;

GameEngineMock::GameEngineMock() :
	m_state(0),
	m_grid(2, 2),
	m_callsToUpdateGameState(0)
{
	m_level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	m_level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	m_state = new GameState(m_level, 2, m_idCreator, m_idCreator);
}

GameEngineMock::~GameEngineMock()
{
	delete m_state;
}

void GameEngineMock::updateGameState(const map<unsigned int, InputState> &, double)
{
	++m_callsToUpdateGameState;
}

const GameState &GameEngineMock::getGameState() const
{
	return *m_state;
}

Grid &GameEngineMock::getGrid()
{
	return m_grid;
}

vector<unsigned int> GameEngineMock::getAllPossiblePlayerIDs() const
{
	return m_state->getAllPossiblePlayerIDs();
}

unsigned int GameEngineMock::getCallsToUpdateGameState() const
{
	return m_callsToUpdateGameState;
}
