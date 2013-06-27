#include "gameloop.h"
#include "common/inputfetcher.h"
#include "common/gameengine.h"
#include "common/graphicdrawer.h"
#include "common/stopwatch.h"
#include <unistd.h>

using namespace Common;
using namespace Main;
using namespace std;

GameLoop::GameLoop(InputFetcher &inputFetcher, Common::GameEngine &gameEngine, GraphicDrawer &graphicDrawer) :
	m_inputFetcher(inputFetcher),
	m_gameEngine(gameEngine),
	m_graphicDrawer(graphicDrawer),
	m_stopped(false),
	m_paused(false),
	m_onceStarted(false),
	m_maximumFramesPerSecond(60),
	m_minimumTimeStep(1.0/m_maximumFramesPerSecond),
	m_weightOfOldAverage(9.0/10),
	m_weightOfNewTime(1 - m_weightOfOldAverage),
	m_movingAverageOfTimeStep(m_minimumTimeStep),
	m_framesPerSecond(0),
	m_computerEnemyInputFetcher(m_gameEngine.getGrid(), m_gameEngine.getGameState(), m_gameEngine.getGameState().getSecondPlayerState().getId())
{
	setConstructionFinished();
}

GameLoop::~GameLoop()
{
	stop();
	if (m_onceStarted)
		waitTillFinished();
}

void GameLoop::start()
{
	m_onceStarted = true;
	m_pausedMutex.lock();
	m_paused = false;
	m_pausedMutex.unlock();
	m_start.send();
}

void GameLoop::stop()
{
	m_stoppedMutex.lock();
	m_stopped = true;
	m_stoppedMutex.unlock();
	m_start.send(); // we need to start again, because otherwise the thread will never stop
}

void GameLoop::pause()
{
	m_pausedMutex.lock();
	m_paused = true;
	m_pausedMutex.unlock();
}

bool GameLoop::isPaused()
{
	m_pausedMutex.lock();
	bool paused = m_paused;
	m_pausedMutex.unlock();
	return paused;
}

double GameLoop::getFramesPerSecond()
{
	double result;
	m_performanceInformationMutex.lock();
	result = m_framesPerSecond;
	m_performanceInformationMutex.unlock();
	return result;
}

void GameLoop::execute()
{
	bool run = true;

	m_start.wait();
	m_start.reset();
	StopWatch watch;
	const Common::GameState &gameState = m_gameEngine.getGameState();
	vector<unsigned int> playerIDs = gameState.getAllNotDestroyedPlayerIDs();

	while (run)
	{
		double timeWithoutWait = watch.getTimeAndRestart();
		double time = timeWithoutWait;
		double timeToWait = m_minimumTimeStep - timeWithoutWait;

		if (timeToWait > 0)
		{
			StopWatch watchForWait;
			watchForWait.restart();
			usleep(timeToWait*1000000);
			time += timeToWait;
		}

		updateMovingAverageOfTime(time);
		updateFPS();

		/*!
		 * @todo Remove this code and feed the input states direct into
		 * the game engine, when the input fetcher supports it.
		 * It should look like this: m_gameEngine.updateGameState(m_inputFetcher.getInputStates(), time);
		 */

		// begin of temporary code
		map<unsigned int, InputState> inputStates;
		inputStates[playerIDs.front()] = m_inputFetcher.getInputState();
		inputStates[playerIDs.back()] = m_computerEnemyInputFetcher.getInputState();
		m_gameEngine.updateGameState(inputStates, time);
		// end of temporary code

		/*!
		 * @todo catchPlayerInformation should only get PlayerIDs of local Players, not all.
		 */

		catchPlayerInformation(gameState.getAllNotDestroyedHumanPlayerIDs());

		m_graphicDrawer.draw(gameState);

		m_pausedMutex.lock();
		bool pause = m_paused;
		m_pausedMutex.unlock();

		if (pause)
		{
			m_start.wait();
			m_start.reset();
		}

		run = !isStopped();

		if(gameState.getAllNotDestroyedPlayerIDs().size() <= 1)
			run = false;

	}
}

void GameLoop::catchPlayerInformation(const vector<unsigned int> &playerIDs)
{
	m_playerInformationMutex.lock();
	m_playerInformation.clear();

	for (size_t y = 0; y < playerIDs.size(); y++)
	{
		m_playerInformation.push_back(playerIDs.at(y));
		m_playerInformation.push_back(m_gameEngine.getGameState().getPlayerStateById(playerIDs.at(y)).getMaxBombs());
		m_playerInformation.push_back(m_gameEngine.getGameState().getPlayerStateById(playerIDs.at(y)).getDestructionRangeOfNewBombs());
	}
	m_playerInformationMutex.unlock();
}

void GameLoop::updateMovingAverageOfTime(double time)
{
	m_movingAverageOfTimeStep = m_movingAverageOfTimeStep*m_weightOfOldAverage + time*m_weightOfNewTime;
}

void GameLoop::updateFPS()
{
	m_performanceInformationMutex.lock();
	m_framesPerSecond = 1/m_movingAverageOfTimeStep;
	m_performanceInformationMutex.unlock();
}

bool GameLoop::isStopped()
{
	bool result;
	m_stoppedMutex.lock();
	result = m_stopped;
	m_stoppedMutex.unlock();
	return result;
}

vector<unsigned int> GameLoop::getPlayerInformation()
{
	m_playerInformationMutex.lock();
	vector<unsigned int> result;
	result = m_playerInformation;
	m_playerInformationMutex.unlock();
	return result;
}
