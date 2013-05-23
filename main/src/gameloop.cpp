#include "gameloop.h"
#include "inputfetcher.h"
#include "gameengine.h"
#include "graphicdrawer.h"
#include "stopwatch.h"
#include <unistd.h>

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
	StopWatch watch;

	while (run)
	{
		double time = watch.getTimeAndRestart();
		m_gameEngine.updateGameState(m_inputFetcher.getInputState(), time);

		m_graphicDrawer.draw(m_gameEngine.getGameState());

		m_stoppedMutex.lock();
		if (m_stopped)
			run = false;
		m_stoppedMutex.unlock();

		// @todo remove this and run as fast as possible
		usleep(1000);
	}
}
