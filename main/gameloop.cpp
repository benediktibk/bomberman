#include "gameloop.h"
#include "common/inputfetcher.h"
#include "common/gameengine.h"
#include "common/graphicdrawer.h"
#include "common/stopwatch.h"
#include <unistd.h>

using namespace Common;
using namespace Main;

GameLoop::GameLoop(InputFetcher &inputFetcher, Common::GameEngine &gameEngine, GraphicDrawer &graphicDrawer) :
	m_inputFetcher(inputFetcher),
	m_gameEngine(gameEngine),
	m_graphicDrawer(graphicDrawer),
	m_stopped(false),
	m_maximumFramesPerSecond(60),
	m_minimumTimeStep(1.0/m_maximumFramesPerSecond),
	m_framesPerSecond(0),
	m_percentageOfTimeNotSleeping(0),
	m_computerEnemyInputFetcher(m_gameEngine.getGrid(), m_gameEngine.getGameState(), m_gameEngine.getAllPossiblePlayerIDs()[1])
{ }

GameLoop::~GameLoop()
{
	stop();
	if (m_start.isSignalSent())
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

void GameLoop::execute()
{
	bool run = true;

	m_start.wait();
	StopWatch watch;
	StopWatch watchRealCalculatingTime;
	double realCalculatingTime = 0;
	std::vector<unsigned int> playerIDs = m_gameEngine.getAllPossiblePlayerIDs();

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
			timeWaited=(m_minimumTimeStep - timeWithoutWait);
			time = timeWaited + timeWithoutWait;
		}
		else
			time = timeWithoutWait;

		m_performanceInformationMutex.lock();
		m_framesPerSecond = static_cast<unsigned int>(1/time);
		m_percentageOfTimeNotSleeping = realCalculatingTime/time;
		m_performanceInformationMutex.unlock();

		watchRealCalculatingTime.restart();

		/*!
		 * @todo Remove this code and feed the input states direct into
		 * the game engine, when the input fetcher supports it.
		 * It should look like this: m_gameEngine.updateGameState(m_inputFetcher.getInputStates(), time);
		 */

		// begin of temporary code
		std::map<unsigned int, InputState> inputStates;
		inputStates[playerIDs.front()] = m_inputFetcher.getInputState();
		inputStates[playerIDs.back()] = m_computerEnemyInputFetcher.getInputState();
		m_gameEngine.updateGameState(inputStates, time);
		// end of temporary code

		m_graphicDrawer.draw(m_gameEngine.getGameState());
		realCalculatingTime = watchRealCalculatingTime.getTimeAndRestart();

		m_stoppedMutex.lock();
		if (m_stopped)
			run = false;
		m_stoppedMutex.unlock();
	}
}
