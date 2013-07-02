#ifndef GAMEENGINE_ALLPLAYERINPUTFETCHER_H
#define GAMEENGINE_ALLPLAYERINPUTFETCHER_H

#include "common/inputstate.h"
#include "common/inputfetcher.h"
#include "gameengine/computerenemyinputfetcher.h"

namespace Common
{
	class InputFetcher;
	class InputState;
}

namespace GameEngine
{
	class AllPlayerInputFetcher:
			public Common::InputFetcher
	{
	public:
		AllPlayerInputFetcher(Common::InputFetcher &input,std::vector<GameEngine::ComputerEnemyInputFetcher*> computer);

		virtual void setAllPossiblePlayerIDs(const std::vector<unsigned int> &playerIDs);
		virtual std::map<unsigned int, Common::InputState> getInputStates();

	private:
		std::map<unsigned int, Common::InputState> m_inputStates;
		Common::InputFetcher &m_humanInputFetcher;
		std::vector<GameEngine::ComputerEnemyInputFetcher*> m_compInputFetcher;
	};
}

#endif
