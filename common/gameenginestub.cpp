#include "common/gameenginestub.h"

using namespace Common;
using namespace std;

GameEngineStub::GameEngineStub() :
	m_state(0),
	m_grid(2, 2)
{
	m_level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	m_level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	m_state = new GameState(m_level, 2, 0, m_idCreator, m_idCreator);
}

GameEngineStub::~GameEngineStub()
{
	delete m_state;
}

void GameEngineStub::updateGameState(const map<unsigned int, InputState> &, double)
{ }

const GameState &GameEngineStub::getGameState() const
{
	return *m_state;
}

Grid &GameEngineStub::getGrid()
{
	return m_grid;
}
