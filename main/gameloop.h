#ifndef MAIN_GAMELOOP_H
#define MAIN_GAMELOOP_H

#include "threading/thread.h"
#include "threading/mutex.h"
#include "threading/signal.h"
#include "gameengine/computerenemyinputfetcher.h"

namespace Common
{
	class GameEngine;
	class InputFetcher;
	class GameState;
	class GraphicDrawer;
}

namespace Main
{
	class GameLoop :
			public Threading::Thread
	{
	public:
		GameLoop(Common::InputFetcher &inputFetcher, Common::GameEngine &gameEngine, Common::GraphicDrawer &graphicDrawer);
		virtual ~GameLoop();

		void start();
		void stop();
		void pause();
		bool isPaused();
		unsigned int getFramesPerSecond();
		double percentageOfTimeNotSleeping();
		std::vector<unsigned int> getPlayerInformation();

	private:
		void catchPlayerInformation(std::vector<unsigned int> playerIDs);

	protected:
		virtual void execute();

	private:
		Common::InputFetcher &m_inputFetcher;
		Common::GameEngine &m_gameEngine;
		Common::GraphicDrawer &m_graphicDrawer;
		Threading::Mutex m_stoppedMutex;
		Threading::Mutex m_pausedMutex;
		bool m_stopped;
		bool m_paused;
		bool m_onceStarted;
		const unsigned int m_maximumFramesPerSecond;
		//! we need a minimum time step, otherwise the physic simulator has problems
		const double m_minimumTimeStep;
		unsigned int m_framesPerSecond;
		Threading::Mutex m_performanceInformationMutex;
		double m_percentageOfTimeNotSleeping;
		Threading::Signal m_start;
		GameEngine::ComputerEnemyInputFetcher m_computerEnemyInputFetcher;
		Threading::Mutex m_playerInformationMutex;
		std::vector<unsigned int> m_playerInformation;
	};
}

#endif
