#ifndef GAMEENGINE_GAMEENGINEIMPL_H
#define GAMEENGINE_GAMEENGINEIMPL_H

#include "common/gameengine.h"
#include "common/uniqueidcreator.h"
#include "common/leveldefinition.h"

namespace Physic
{
	class GamePhysicSimulator;
}

namespace GameEngine
{
	class Grid;

	class GameEngineImpl :
			public Common::GameEngine
	{
	public:
		GameEngineImpl(const Common::LevelDefinition &level);
		virtual ~GameEngineImpl();

		virtual void updateGameState(const Common::InputState &inputState, double time);
		virtual const Common::GameState& getGameState() const;
		Common::GameState& getGameState();
		double getTimeTillPlayerReachesGridPoint() const;

	private:
		void updatePlayerPosition();
		void updatePlayerVelocity();
		void setPlayerSpeedIfMoreThanOneDirectionIsSelected();
		void setPlayerSpeedIntoOnlySelectedDirection();
		void setPlayerSpeedToNull();
		void updateBombs();
		void placeBombs();

	private:
		Common::InputState m_inputState;
		Common::UniqueIdCreator m_bombids;
		Common::UniqueIdCreator m_wallids;
		Common::UniqueIdCreator m_playerIds;
		Common::GameState m_gameState;
		Common::PlayerState &m_playerState;
		double m_elapsedTime;
		Grid *m_grid;
		bool m_firstGameStateUpdate;
		Physic::GamePhysicSimulator *m_simulator;
	};
}

#endif
