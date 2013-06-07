#ifndef COMMON_GAMEENGINESTUB_H
#define COMMON_GAMEENGINESTUB_H

#include "common/gameengine.h"
#include "common/gamestate.h"
#include "common/uniqueidcreator.h"
#include "common/leveldefinition.h"

namespace Common
{
	class GameEngineStub :
			public GameEngine
	{
	public:
		GameEngineStub();

		virtual void updateGameState(const std::map<unsigned int, InputState> &inputStates, double time);
		virtual const GameState& getGameState() const;
		virtual std::vector<unsigned int> getAllPossiblePlayerIDs() const;

	private:
		LevelDefinition m_level;
		UniqueIdCreator m_idCreator;
		GameState m_state;
	};
}

#endif
