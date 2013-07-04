#include "main/gameloop.h"
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

GameLoop::GameLoop(InputFetcher &inputFetcher, Common::GameEngine &gameEngine, GraphicDrawer &graphicDrawer) :
	m_inputFetcher(inputFetcher),
	m_gameEngine(gameEngine),
	m_graphicDrawer(graphicDrawer),
	m_stopped(false),
	m_paused(false),
	m_onceStarted(false),
	m_maximumGameUpdatesPerSecond(60),
	m_minimumTimeStep(1.0/m_maximumGameUpdatesPerSecond),
	m_weightOfOldAverage(9.0/10),
	m_weightOfNewTime(1 - m_weightOfOldAverage),
	m_movingAverageOfTimeStep(m_minimumTimeStep),
	m_gameUpdatesPerSecond(0)
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

double GameLoop::getGameUpdatesPerSecond()
{
	Lock lock(m_performanceInformationMutex);
	return m_gameUpdatesPerSecond;
}

void GameLoop::execute()
{
	bool run = true;

	m_start.wait();
	m_start.reset();
	StopWatch watch;
	const Common::GameState &gameState = m_gameEngine.getGameState();
	double timeForDrawing = 0;

	m_inputFetcher.setAllPossiblePlayerIDs(gameState.getAllNotDestroyedPlayerIDs());

	while (run)
	{
		double timeWithoutWait = watch.getTimeAndRestart() + timeForDrawing;
		double time = timeWithoutWait;
		double timeToWait = m_minimumTimeStep - timeWithoutWait;

		if (timeToWait > 0)
		{
			usleep(timeToWait*1000000);
			time = m_minimumTimeStep;
		}

		updateMovingAverageOfTime(time);
		updateGameUpdatesPerSecond();

		m_gameEngine.updateGameState(m_inputFetcher.getInputStates(), time);
		timeForDrawing = m_graphicDrawer.draw(gameState);

		catchPlayerInformation(gameState.getAllNotDestroyedHumanPlayerIDs());
		pauseIfNecessary();
		run = !isStopped() && !gameState.isGameFinished();
		if(gameState.isGameFinished())
			emit winnerSignal(gameState.getWinnerOfGame());
	}
}

void GameLoop::catchPlayerInformation(const vector<unsigned int> &playerIDs)
{
	Lock lock(m_playerInformationMutex);
	const Common::GameState &gameState = m_gameEngine.getGameState();
	m_playerInformation.clear();

	for (size_t y = 0; y < playerIDs.size(); y++)
	{
		unsigned int playerID = playerIDs[y];
		Common::PlayerInformation playerInformation;
		const Common::PlayerState &playerState = gameState.getPlayerStateById(playerID);
		playerInformation.setPlayerId(playerID);
		playerInformation.setRangeCounter(playerState.getDestructionRangeOfNewBombs());
		playerInformation.setBombCounter(playerState.getMaxBombs());
		playerInformation.setSpeedCounter(playerState.getSpeed());
		m_playerInformation.push_back(playerInformation);
	}
}

void GameLoop::updateMovingAverageOfTime(double time)
{
	m_movingAverageOfTimeStep = m_movingAverageOfTimeStep*m_weightOfOldAverage + time*m_weightOfNewTime;
}

void GameLoop::updateGameUpdatesPerSecond()
{
	Lock lock(m_performanceInformationMutex);
	m_gameUpdatesPerSecond = 1/m_movingAverageOfTimeStep;
}

bool GameLoop::isStopped()
{
	Lock lock(m_stoppedMutex);
	return m_stopped;
}

vector<Common::PlayerInformation> GameLoop::getPlayerInformation()
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
