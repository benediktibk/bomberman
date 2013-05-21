#include "gameloop.h"
#include "inputfetcher.h"
#include "gameengine.h"
#include "graphicdrawer.h"

using namespace Common;
using namespace Main;

GameLoop::GameLoop(InputFetcher &inputFetcher, GameEngine &gameEngine, GraphicDrawer &graphicDrawer) :
	m_inputFetcher(inputFetcher),
	m_gameEngine(gameEngine),
	m_graphicDrawer(graphicDrawer),
	m_stopped(false)
{ }

GameLoop::~GameLoop()
{
	stop();
	waitTillFinished();
}

void GameLoop::stop()
{
	m_stoppedMutex.lock();
	m_stopped = true;
	m_stoppedMutex.unlock();
}

void GameLoop::execute()
{
	bool run = true;
	m_gameEngine.resetTime();

	while (run)
	{
		m_gameEngine.updateGameState(m_inputFetcher.getInputState());

		m_graphicDrawer.draw(m_gameEngine.getGameState());

		m_stoppedMutex.lock();
		if (m_stopped)
			run = false;
		m_stoppedMutex.unlock();
	}
}
