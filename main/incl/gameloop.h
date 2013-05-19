#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "thread.h"

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
	GameLoop(Common::InputFetcher *inputFetcher, Common::GameEngine *gameEngine, Common::GraphicDrawer *graphicDrawer);
	virtual ~GameLoop();

protected:
	virtual void execute();

private:
	Common::InputFetcher *m_inputFetcher;
	Common::GameEngine *m_gameEngine;
	Common::GraphicDrawer *m_graphicDrawer;
};
}

#endif
