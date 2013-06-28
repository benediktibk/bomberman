#ifndef COMMON_ALLPLAYERINPUTFETCHER_H
#define COMMON_ALLPLAYERINPUTFETCHER_H

#include "common/inputstate.h"
#include "common/inputfetcher.h"
#include "gameengine/computerenemyinputfetcher.h"
namespace Common
{


	class allPlayerInputFetcher:
			public InputFetcher
	{
	public:
	allPlayerInputFetcher(InputFetcher &input,std::vector<GameEngine::ComputerEnemyInputFetcher*> computer, size_t playerCount);

	virtual void setAllPossiblePlayerIDs(const std::vector<unsigned int> &playerIDs);
	virtual std::map<unsigned int, InputState> getInputStates();
	void setAllPossiblePlayerIds(std::vector<unsigned int> allPossiblePlayerIds);
	Common::InputState getInputStateByID( unsigned int playerID);

	private:
	std::map<unsigned int, InputState> m_inputStates;
	Common::InputState m_inputStatePlayer1;
	Common::InputFetcher &m_inputFetcher;
	std::vector<GameEngine::ComputerEnemyInputFetcher*> m_compInputFetcher;
	std::vector<Common::InputState> m_computerInputStates;
	std::vector<unsigned int> m_playerIds;
	std::vector<unsigned int> m_enemyIds;
	bool m_gameModeIsSinglePlayer;

	};
}


#endif // ALLPLAYERINPUTFETCHER_H
