#ifndef GAMEENGINEIMPL_H
#define GAMEENGINEIMPL_H

#include "gameengine.h"

namespace GameEngine
{
class GameEngineImpl :
		public Common::GameEngine
{
public:
	virtual void updateGameState(const Common::InputState &inputState);
	virtual const Common::GameState& getGameState();

private:
	Common::InputState m_inputState;
	Common::GameState m_gameState;
};
}

#endif
