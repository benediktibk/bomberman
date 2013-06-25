#ifndef COMMON_GAMEENGINE_H
#define COMMON_GAMEENGINE_H

#include "common/inputstate.h"
#include "common/gamestate.h"
#include "common/grid.h"
#include <vector>
#include <map>

namespace Common
{
	class GameEngine
	{
	public:
		virtual void updateGameState(const std::map<unsigned int, InputState> &inputStates, double time) = 0;
		virtual const GameState& getGameState() const = 0;
		virtual Grid &getGrid() = 0;
		virtual std::vector<unsigned int> getAllPossiblePlayerIDs() const = 0;

		virtual ~GameEngine() { }
	};
}

#endif
