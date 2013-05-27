#ifndef COMMON_GAMEENGINE_H
#define COMMON_GAMEENGINE_H

#include "inputstate.h"
#include "gamestate.h"

namespace Common
{
class GameEngine
{
public:
	virtual void updateGameState(const InputState &inputState, double time) = 0;
	virtual const GameState& getGameState() = 0;

	virtual ~GameEngine() { }
};
}

#endif
