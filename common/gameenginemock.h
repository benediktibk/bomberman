#ifndef COMMON_GAMEENGINEMOCK_H
#define COMMON_GAMEENGINEMOCK_H

#include "common/gameengine.h"
#include "common/gamestate.h"
#include "common/uniqueidcreator.h"
#include "common/leveldefinition.h"

namespace Common
{
	class GameEngineMock :
			public GameEngine
	{
	public:
		GameEngineMock();

		virtual void updateGameState(const InputState &inputState, double time);
		virtual const GameState& getGameState() const;

		unsigned int getCallsToUpdateGameState() const;

	private:
		LevelDefinition m_level;
		UniqueIdCreator m_idCreator;
		GameState m_state;
		unsigned int m_callsToUpdateGameState;
	};
}

#endif
