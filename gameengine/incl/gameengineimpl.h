#ifndef GAMEENGINEIMPL_H
#define GAMEENGINEIMPL_H

#include "gameengine.h"
#include "stopwatch.h"

namespace GameEngine
{
class GameEngineImpl :
		public Common::GameEngine
{
public:
	virtual void updateGameState(const Common::InputState &inputState);
	virtual void resetTime();
	virtual const Common::GameState& getGameState();

private:
	Common::InputState m_inputState;
	Common::GameState m_gameState;
	Common::StopWatch m_stopWatch;
};
}

#endif
