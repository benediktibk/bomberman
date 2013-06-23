#include "gameengine/computerenemyinputfetcher.h"
#include "gameengine/routergrid.h"
#include "common/randomdecision.h"

using namespace Common;
using namespace GameEngine;

ComputerEnemyInputFetcher::ComputerEnemyInputFetcher(Grid &grid, const Common::GameState &gameState, unsigned int playerId) :
	m_router(new RouterGrid(grid, gameState, playerId))
{ }

ComputerEnemyInputFetcher::~ComputerEnemyInputFetcher()
{
	delete m_router;
}

InputState ComputerEnemyInputFetcher::getInputState()
{
	RandomDecision noKeyPressed(0.75);
	RandomDecision KeyPressed(0.25);

	if(KeyPressed.decide())
		m_inputState.setDownKeyPressed();
	if(KeyPressed.decide())
		m_inputState.setUpKeyPressed();
	if(KeyPressed.decide())
		m_inputState.setLeftKeyPressed();
	if(KeyPressed.decide())
		m_inputState.setRightKeyPressed();

	if(noKeyPressed.decide())
	{
		m_inputState.setDownKeyNotPressed();
		m_inputState.setLeftKeyNotPressed();
		m_inputState.setRightKeyNotPressed();
		m_inputState.setUpKeyNotPressed();
	}

	return m_inputState;
}

std::map<unsigned int, InputState> ComputerEnemyInputFetcher::getInputStates()
{
	std::map<unsigned int, InputState> result;
	return result;
}