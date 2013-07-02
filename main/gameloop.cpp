#include "gameloop.h"
#include "common/inputfetcher.h"
#include "common/gameengine.h"
#include "common/graphicdrawer.h"
#include "common/stopwatch.h"
#include "threading/lock.h"
#include <unistd.h>
#include <assert.h>

using namespace Common;
using namespace Main;
using namespace std;
using namespace GameEngine;
using namespace Threading;

GameLoop::GameLoop(InputFetcher &inputFetcher, Common::GameEngine &gameEngine, GraphicDrawer &graphicDrawer, GameEngine::ComputerEnemyLevel computerEnemyLevel) :
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
	m_framesPerSecond(0)
{
	const GameState &gameState = m_gameEngine.getGameState();
	m_allInput = new GameEngine::AllPlayerInputFetcher(m_inputFetcher, gameState, computerEnemyLevel, m_gameEngine.getGrid());

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
	Lock lock(m_pausedMutex);
	m_paused = true;
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
	Lock lock(m_performanceInformationMutex);
	return m_framesPerSecond;
}

void GameLoop::execute()
{
	bool run = true;

	m_start.wait();
	m_start.reset();
	StopWatch watch;
	const Common::GameState &gameState = m_gameEngine.getGameState();

	m_allInput->setAllPossiblePlayerIDs(gameState.getAllNotDestroyedPlayerIDs());

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

		m_gameEngine.updateGameState(m_allInput->getInputStates(),time);

		m_graphicDrawer.draw(gameState);

		catchPlayerInformation(gameState.getAllNotDestroyedHumanPlayerIDs());
		pauseIfNecessary();
		run = !isStopped() && !gameState.isGameFinished();
		if(gameState.isGameFinished())
			emit winnerSignal(m_gameEngine.getGameState().getWinnerOfGame().c_str());
	}
}

void GameLoop::catchPlayerInformation(const vector<unsigned int> &playerIDs)
{
	Lock lock(m_playerInformationMutex);
	m_playerInformation.clear();

	for (size_t y = 0; y < playerIDs.size(); y++)
	{
		m_playerInformation.push_back(playerIDs.at(y));
		m_playerInformation.push_back(m_gameEngine.getGameState().getPlayerStateById(playerIDs.at(y)).getMaxBombs());
		m_playerInformation.push_back(m_gameEngine.getGameState().getPlayerStateById(playerIDs.at(y)).getDestructionRangeOfNewBombs());
	}
}

void GameLoop::updateMovingAverageOfTime(double time)
{
	m_movingAverageOfTimeStep = m_movingAverageOfTimeStep*m_weightOfOldAverage + time*m_weightOfNewTime;
}

void GameLoop::updateFPS()
{
	Lock lock(m_performanceInformationMutex);
	m_framesPerSecond = 1/m_movingAverageOfTimeStep;
}

bool GameLoop::isStopped()
{
	Lock lock(m_stoppedMutex);
	return m_stopped;
}

vector<unsigned int> GameLoop::getPlayerInformation()
{
	Lock lock(m_playerInformationMutex);
	return m_playerInformation;
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
