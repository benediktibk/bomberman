#ifndef GAMEENGINE_GAMEENGINEIMPL_H
#define GAMEENGINE_GAMEENGINEIMPL_H

#include "common/gameengine.h"
#include "common/uniqueidcreator.h"
#include "common/leveldefinition.h"
#include "common/gridpoint.h"

namespace Common
{
	class Grid;
}

namespace Physic
{
	class GamePhysicSimulator;
}

namespace GameEngine
{
	class GameEngineImpl :
			public Common::GameEngine
	{
	public:
		GameEngineImpl(const Common::LevelDefinition &level, unsigned int humanPlayerCount, unsigned int computerEnemyCount);
		virtual ~GameEngineImpl();

		virtual void updateGameState(const std::map<unsigned int, Common::InputState> &inputStates, double time);
		virtual Common::Grid &getGrid();
		virtual const Common::GameState& getGameState() const;
		Common::GameState& getGameState();
		double getTimeTillOnePlayerReachesGridPoint() const;
		double getTimeTillPlayerReachesGridPoint(const Common::PlayerState &player) const;
		void addPowerUpOfTypeAtPosition(Common::PowerUpType powerUpType, Common::Point position);

	private:
		void updatePlayerPositions();
		void updatePlayerVelocities();
		void updatePlayerVelocity(Common::PlayerState &player, const Common::InputState &input);
		void updatePlayerWithBombCollisions();
		void setPlayerSpeedIfMoreThanOneDirectionIsSelected(Common::PlayerState &player, const Common::InputState &input);
		void setPlayerSpeedIntoOnlySelectedDirection(Common::PlayerState &player, const Common::InputState &input);
		void setPlayerSpeedIntoIntoDirection(Common::PlayerState &player, const Common::InputState &input);
		void setPlayerSpeedToNull(Common::PlayerState &player);
		void updateBombs();
		void placeBombs();
		void placeBombForPlayer(Common::PlayerState &player, const Common::InputState &input);
		void addPowerUp(Common::PowerUpState *powerUp);
		void addRandomPowerUpAtPosition(Common::Point position);
		void removeAllObjectsWithDestroyedFlagFromGrid();
		void playerGetsPowerUp();

	private:
		std::map<unsigned int, Common::InputState> m_inputStates;
		Common::UniqueIdCreator m_bombids;
		Common::UniqueIdCreator m_wallids;
		Common::UniqueIdCreator m_playerIds;
		Common::UniqueIdCreator m_powerUpIds;
		Common::GameState m_gameState;
		double m_elapsedTime;
		Common::Grid *m_grid;
		bool m_firstGameStateUpdate;
		Physic::GamePhysicSimulator *m_simulator;
		unsigned int m_levelWidth;
		unsigned int m_levelHeight;
	};
}

#endif
