#ifndef GAMEENGINE_COMPUTERENEMYINPUTFETCHER_H
#define GAMEENGINE_COMPUTERENEMYINPUTFETCHER_H

#include "common/inputfetcher.h"
#include "common/inputstate.h"
#include <vector>
#include <map>

namespace Common
{
	class GameState;
	class Grid;
}

namespace GameEngine
{
	class RouterGrid;

	class ComputerEnemyInputFetcher :
		public Common::InputFetcher
	{
	public:
		ComputerEnemyInputFetcher(Common::Grid &grid, const Common::GameState &gameState, unsigned int playerId);
		virtual ~ComputerEnemyInputFetcher();

		virtual std::map<unsigned int, Common::InputState> getInputStates();
		virtual Common::InputState getInputState();

	private:
		Common::InputState m_inputState;
		RouterGrid *m_router;
	};
}

#endif
