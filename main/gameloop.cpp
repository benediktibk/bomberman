#include "gameloop.h"
#include "common/inputfetcher.h"
#include "common/gameengine.h"
#include "common/stopwatch.h"
#include <unistd.h>

using namespace Common;
using namespace Main;

GameLoop::GameLoop(InputFetcher &inputFetcher, GameEngine &gameEngine) :
	m_inputFetcher(inputFetcher),
	m_gameEngine(gameEngine),
	m_stopped(false),
	m_maximumFramesPerSecond(60),
	m_minimumTimeStep(1.0/m_maximumFramesPerSecond),
	m_framesPerSecond(0),
	m_percentageOfTimeNotSleeping(0)
{ }

GameLoop::~GameLoop()
{
	stop();
	setGuiUpdateFinished();
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
	m_performanceInformationMutex.lock();
	result = m_framesPerSecond;
	m_performanceInformationMutex.unlock();
	return result;
}

double GameLoop::percentageOfTimeNotSleeping()
{
	m_performanceInformationMutex.lock();
	double result = m_percentageOfTimeNotSleeping;
	m_performanceInformationMutex.unlock();
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
	StopWatch watchRealCalculatingTime;
	double realCalculatingTime = 0;

	while (run)
	{
		double timeWithoutWait = watch.getTimeAndRestart();
		double timeWaited = 0;
		double time = 0;

		if (timeWithoutWait < m_minimumTimeStep)
		{
			StopWatch watchForWait;
			watchForWait.restart();
			usleep((m_minimumTimeStep - timeWithoutWait)*1000000);
			timeWaited = watchForWait.getTimeAndRestart();
			time = timeWaited + timeWithoutWait;
		}
		else
			time = timeWithoutWait;

		m_performanceInformationMutex.lock();
		m_framesPerSecond = static_cast<unsigned int>(1/time);
		m_percentageOfTimeNotSleeping = realCalculatingTime/time;
		m_performanceInformationMutex.unlock();

		watchRealCalculatingTime.restart();
		m_gameEngine.updateGameState(m_inputFetcher.getInputState(), time);

		emit guiUpdateNecessary(&(m_gameEngine.getGameState()));
		m_guiUpdateFinished.wait();
		m_guiUpdateFinished.reset();

		realCalculatingTime = watchRealCalculatingTime.getTimeAndRestart();

		m_stoppedMutex.lock();
		if (m_stopped)
			run = false;
		m_stoppedMutex.unlock();
	}
}
