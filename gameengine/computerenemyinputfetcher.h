#ifndef GAMEENGINE_COMPUTERENEMYINPUTFETCHER_H
#define GAMEENGINE_COMPUTERENEMYINPUTFETCHER_H

#include "common/inputfetcher.h"
#include "common/inputstate.h"
#include "common/playerstate.h"
#include <vector>
#include <map>

namespace Common
{
	class GameState;
	class Grid;
}

namespace GameEngine
{
	class Router;

	class ComputerEnemyInputFetcher :
		public Common::InputFetcher
	{
	public:
		ComputerEnemyInputFetcher(Common::Grid &grid, const Common::GameState &gameState, unsigned int playerID);
		virtual ~ComputerEnemyInputFetcher();

		virtual std::map<unsigned int, Common::InputState> getInputStates();
		virtual Common::InputState getInputState();

	private:
		void setInputStateIntoDirection(Common::PlayerState::PlayerDirection direction);

	private:
		Common::InputState m_inputState;
		Router *m_router;
		const Common::GameState &m_gameState;
		unsigned int m_playerID;
	};
}

#endif
