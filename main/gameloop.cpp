#include "gameloop.h"
#include "inputfetcher.h"
#include "gameengine.h"
#include "stopwatch.h"
#include <unistd.h>

using namespace Common;
using namespace Main;

GameLoop::GameLoop(InputFetcher &inputFetcher, GameEngine &gameEngine) :
	m_inputFetcher(inputFetcher),
	m_gameEngine(gameEngine),
	m_stopped(false),
	m_maximumFramesPerSecond(1000),
	m_minimumTimeStep(1.0/m_maximumFramesPerSecond),
	m_framesPerSecond(0)
{ }

GameLoop::~GameLoop()
{
	setGuiUpdateFinished();
	stop();
	waitTillFinished();
}

void GameLoop::start()
{
	m_start.send();
}

void GameLoop::stop()
{
	m_stoppedMutex.lock();
	m_stopped = true;
	m_stoppedMutex.unlock();
}

unsigned int GameLoop::getFramesPerSecond()
{
	unsigned int result;
	m_framesPerSecondMutex.lock();
	result = m_framesPerSecond;
	m_framesPerSecondMutex.unlock();
	return result;
}

void GameLoop::setGuiUpdateFinished()
{
	m_guiUpdateFinished.send();
}

void GameLoop::execute()
{
	bool run = true;

	m_start.wait();
	StopWatch watch;

	while (run)
	{
		double timeWithoutWait = watch.getTimeAndRestart();
		double time = 0;

		if (timeWithoutWait < m_minimumTimeStep)
		{
			StopWatch watchForWait;
			watchForWait.restart();
			usleep((m_minimumTimeStep - timeWithoutWait)*1000000);
			time = watchForWait.getTimeAndRestart() + timeWithoutWait;
		}
		else
			time = timeWithoutWait;

		m_framesPerSecondMutex.lock();
		m_framesPerSecond = static_cast<unsigned int>(1/time);
		m_framesPerSecondMutex.unlock();

		m_gameEngine.updateGameState(m_inputFetcher.getInputState(), time);

		emit guiUpdateNecessary(&(m_gameEngine.getGameState()));
		m_guiUpdateFinished.wait();
		m_guiUpdateFinished.reset();

		m_stoppedMutex.lock();
		if (m_stopped)
			run = false;
		m_stoppedMutex.unlock();
	}
}
