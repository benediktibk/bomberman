#include "gameloop.h"
#include "inputfetcher.h"
#include "gameengine.h"
#include "graphicdrawer.h"

using namespace Common;
using namespace Main;

GameLoop::GameLoop(InputFetcher *inputFetcher, GameEngine *gameEngine, GraphicDrawer *graphicDrawer) :
	m_inputFetcher(inputFetcher),
	m_gameEngine(gameEngine),
	m_graphicDrawer(graphicDrawer)
{ }

GameLoop::~GameLoop()
{
	delete m_inputFetcher;
	delete m_gameEngine;
	delete m_graphicDrawer;
}

void GameLoop::execute()
{
	while (true)
	{
		InputState inputState = m_inputFetcher->getInputState();

		m_gameEngine->updateGameState(inputState);

		m_graphicDrawer->draw(m_gameEngine->getGameState());
	}
}
