#ifndef GAMEENGINE_ALLPLAYERINPUTFETCHER_H
#define GAMEENGINE_ALLPLAYERINPUTFETCHER_H

#include "common/inputstate.h"
#include "common/inputfetcher.h"
#include "gameengine/computerenemylevel.h"
#include <vector>
#include <map>

namespace Common
{
	class GameState;
	class Grid;
}

namespace GameEngine
{
	class ComputerEnemyInputFetcher;

	class AllPlayerInputFetcher:
			public Common::InputFetcher
	{
	public:
		AllPlayerInputFetcher(Common::InputFetcher &input, const Common::GameState &gameState, ComputerEnemyLevel computerEnemyLevel, Common::Grid &grid);
		virtual ~AllPlayerInputFetcher();

		virtual void setAllPossiblePlayerIDs(const std::vector<unsigned int> &playerIDs);
		virtual std::map<unsigned int, Common::InputState> getInputStates();

	private:
		std::map<unsigned int, Common::InputState> m_inputStates;
		Common::InputFetcher &m_humanInputFetcher;
		std::vector<GameEngine::ComputerEnemyInputFetcher*> m_computerEnemyInputFetchers;
		const Common::GameState &m_gameState;
	};
}

#endif
