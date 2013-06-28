#include "gameloop.h"
#include "common/inputfetcher.h"
#include "common/gameengine.h"
#include "common/graphicdrawer.h"
#include "common/stopwatch.h"
#include "gameengine/computerenemyinputfetchereasy.h"
#include "gameengine/computerenemyinputfetchermedium.h"
#include "gameengine/computerenemyinputfetcherhard.h"
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
	m_framesPerSecond(0),
	m_computerEnemyInputFetcher()
{
	const GameState &gameState = m_gameEngine.getGameState();
	vector<unsigned int> computerEnemyIDs = gameState.getAllNotDestroyedComputerEnemyIDs();
	for (size_t i = 0; i < computerEnemyIDs.size(); ++i)
	{
		switch (computerEnemyLevel)
		{
		case ComputerEnemyLevelEasy:
			m_computerEnemyInputFetcher.push_back(new GameEngine::ComputerEnemyInputFetcherEasy(m_gameEngine.getGrid(), gameState));
			break;
		case ComputerEnemyLevelMedium:
			m_computerEnemyInputFetcher.push_back(new GameEngine::ComputerEnemyInputFetcherMedium(m_gameEngine.getGrid(), gameState));
			break;
		case ComputerEnemyLevelHard:
			m_computerEnemyInputFetcher.push_back(new GameEngine::ComputerEnemyInputFetcherHard(m_gameEngine.getGrid(), gameState));
			break;
		}
	}
    
    vector<unsigned int> playerIDs = gameState.getAllNotDestroyedPlayerIDs();
    m_allInput = new GameEngine::allPlayerInputFetcher(m_inputFetcher,m_computerEnemyInputFetcher,playerIDs.size());
    
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
	vector<unsigned int> computerEnemyIDs = gameState.getAllNotDestroyedComputerEnemyIDs();
	vector<unsigned int> humanPlayerIDs = gameState.getAllNotDestroyedHumanPlayerIDs();

	m_inputFetcher.setAllPossiblePlayerIDs(humanPlayerIDs);
	for (size_t i = 0; i < computerEnemyIDs.size(); ++i)
	{
		vector<unsigned int> playerIDs;
		playerIDs.push_back(computerEnemyIDs[i]);
		m_computerEnemyInputFetcher[i]->setAllPossiblePlayerIDs(playerIDs);
	}

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
