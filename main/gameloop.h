#ifndef MAIN_GAMELOOP_H
#define MAIN_GAMELOOP_H

#include "threading/thread.h"
#include "threading/mutex.h"
#include "threading/signal.h"
#include <QtCore/QObject>

namespace Common
{
	class GameEngine;
	class InputFetcher;
	class GameState;
}

namespace Main
{
class GameLoop :
		public QObject,
		public Threading::Thread
{
	Q_OBJECT

public:
	GameLoop(Common::InputFetcher &inputFetcher, Common::GameEngine &gameEngine);
	virtual ~GameLoop();

	void start();
	void stop();
	unsigned int getFramesPerSecond();
	void setGuiUpdateFinished();

signals:
	void guiUpdateNecessary(const Common::GameState *gameState);

protected:
	virtual void execute();

private:
	Common::InputFetcher &m_inputFetcher;
	Common::GameEngine &m_gameEngine;
	Threading::Mutex m_stoppedMutex;
	bool m_stopped;
	const unsigned int m_maximumFramesPerSecond;
	//! we need a minimum time step, otherwise the physic simulator has problems
	const double m_minimumTimeStep;
	unsigned int m_framesPerSecond;
	Threading::Mutex m_framesPerSecondMutex;
	Threading::Signal m_guiUpdateFinished;
	Threading::Signal m_start;
};
}

#endif
