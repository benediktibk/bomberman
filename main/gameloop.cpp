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
	m_computerEnemyInputFetcher()
{
	const GameState &gameState = m_gameEngine.getGameState();
	vector<unsigned int> computerEnemyIDs = gameState.getAllNotDestroyedComputerEnemyIDs();
	for (size_t i = 0; i < computerEnemyIDs.size(); ++i)
		m_computerEnemyInputFetcher.push_back(new GameEngine::ComputerEnemyInputFetcherHard(m_gameEngine.getGrid(), gameState, computerEnemyIDs[i]));
	setConstructionFinished();
}

GameLoop::~GameLoop()
{
	stop();
	if (m_onceStarted)
		waitTillFinished();

	for (vector<GameEngine::ComputerEnemyInputFetcher*>::iterator i = m_computerEnemyInputFetcher.begin(); i != m_computerEnemyInputFetcher.end(); ++i)
		delete *i;
	m_computerEnemyInputFetcher.clear();
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
	vector<unsigned int> computerEnemyIDs = gameState.getAllNotDestroyedComputerEnemyIDs();
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
		for (size_t i = 0; i < computerEnemyIDs.size(); ++i)
			inputStates[computerEnemyIDs[i]] = m_computerEnemyInputFetcher[i]->getInputState();
		m_gameEngine.updateGameState(inputStates, time);
		// end of temporary code

		m_graphicDrawer.draw(gameState);

		catchPlayerInformation(gameState.getAllNotDestroyedHumanPlayerIDs());
		pauseIfNecessary();
		run = !isStopped() && !gameState.isGameFinished();
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
	m_stoppedMutex.lock();
	bool result = m_stopped;
	m_stoppedMutex.unlock();
	return result;
}

vector<unsigned int> GameLoop::getPlayerInformation()
{
	m_playerInformationMutex.lock();
	vector<unsigned int> result = m_playerInformation;
	m_playerInformationMutex.unlock();
	return result;
}

void GameLoop::pauseIfNecessary()
{
	m_pausedMutex.lock();
	bool pause = m_paused;
	m_pausedMutex.unlock();

	if (pause)
	{
		m_start.wait();
		m_start.reset();
	}
}
