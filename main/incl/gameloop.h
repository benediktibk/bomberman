#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "threadcustom.h"
#include "mutex.h"
#include "signalcustom.h"
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

	void stop();
	unsigned int getFramesPerSecond();
	Threading::Signal& getSignalGuiUpdateFinished();

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
};
}

#endif
