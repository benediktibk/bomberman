#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "thread.h"
#include "mutex.h"

namespace Common
{
	class GameEngine;
	class InputFetcher;
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

	void stop();

protected:
	virtual void execute();

private:
	Common::InputFetcher &m_inputFetcher;
	Common::GameEngine &m_gameEngine;
	Common::GraphicDrawer &m_graphicDrawer;
	Threading::Mutex m_stoppedMutex;
	bool m_stopped;
};
}

#endif
