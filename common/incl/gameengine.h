#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "inputstate.h"
#include "gamestate.h"

namespace Common
{
class GameEngine
{
public:
	virtual void updateGameState(const InputState &inputState) = 0;
	virtual const GameState& getGameState() = 0;

	virtual ~GameEngine() { }
};
}

#endif
