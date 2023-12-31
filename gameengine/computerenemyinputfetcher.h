#ifndef GAMEENGINE_COMPUTERENEMYINPUTFETCHER_H
#define GAMEENGINE_COMPUTERENEMYINPUTFETCHER_H

#include "common/inputfetcher.h"
#include "common/inputstate.h"
#include "common/playerstate.h"
#include "common/gridpoint.h"
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
	class Route;

	class ComputerEnemyInputFetcher :
		public Common::InputFetcher
	{
	public:
		ComputerEnemyInputFetcher(Common::Grid &grid, const Common::GameState &gameState);
		virtual ~ComputerEnemyInputFetcher();

		virtual void setAllPossiblePlayerIDs(const std::vector<unsigned int> &allPossiblePlayerIds);
		virtual std::map<unsigned int, Common::InputState> getInputStates();
		unsigned int getPlayerID();

	protected:
		virtual void calculateInputStateInternal() = 0;
		void calculateInputState();
		void setInputStateIntoDirection(Common::PlayerState::PlayerDirection direction);
		void placeBombIfCloseEnough(const Route &route);
		Router& getRouter();
		Common::GridPoint getPlayerPosition() const;
		unsigned int getDestructionRangeOfNewBombs() const;
		double getPlayerSpeed() const;
		double getBombLifeTime() const;

	private:
		Common::InputState m_inputState;
		Router *m_router;
		Common::Grid &m_grid;
		const Common::GameState &m_gameState;
		unsigned int m_playerID;
		std::map<unsigned int, Common::InputState> m_inputStateWithID;
		const Common::PlayerState *m_player;
	};
}

#endif
