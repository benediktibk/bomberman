#ifndef COMMON_GAMEENGINEMOCK_H
#define COMMON_GAMEENGINEMOCK_H

#include "common/gameengine.h"
#include "common/gamestate.h"
#include "common/uniqueidcreator.h"
#include "common/leveldefinition.h"
#include "common/grid.h"

namespace Common
{
	class GameEngineMock :
			public GameEngine
	{
	public:
		GameEngineMock();
		virtual ~GameEngineMock();

		virtual void updateGameState(const std::map<unsigned int, InputState> &inputStates, double time);
		virtual const GameState& getGameState() const;
		virtual Grid &getGrid();
		virtual std::vector<unsigned int> getAllNotDestroyedPlayerIDs() const;

		unsigned int getCallsToUpdateGameState() const;

	private:
		LevelDefinition m_level;
		UniqueIdCreator m_idCreator;
		GameState *m_state;
		Grid m_grid;
		unsigned int m_callsToUpdateGameState;
	};
}

#endif
