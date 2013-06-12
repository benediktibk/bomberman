#ifndef COMMON_GAMESTATE_H
#define COMMON_GAMESTATE_H

#include "common/playerstate.h"
#include "common/wallstate.h"
#include "common/bombstate.h"
#include "common/leveldefinition.h"
#include "common/uniqueidcreator.h"
#include "common/powerupstate.h"
#include "common/powerupmaxbombstate.h"
#include "common/powerupmaxvelocitystate.h"
#include "common/explodedbombstate.h"
#include <vector>

namespace Common
{
	class GameState
	{
	public:
		GameState(const LevelDefinition &level, unsigned int playerCount, UniqueIdCreator &playerIDCreator, UniqueIdCreator &wallIDCreator);
		~GameState();

		PlayerState& getFirstPlayerState();
		const PlayerState& getFirstPlayerState() const;
		PlayerState& getSecondPlayerState();
		const PlayerState& getSecondPlayerState() const;
		PlayerState& getPlayerStateById(unsigned int playerId);
		const PlayerState& getPlayerStateById(unsigned int playerId) const;
		std::vector<unsigned int> getAllPossiblePlayerIDs() const;
		const std::vector<const PlayerState*>& getAllPlayers() const;
		std::vector<const WallState*> getAllChangedWalls() const;
		size_t getWallCount() const;
		void addWall(WallState* wall);
		std::vector<const BombState*> getAllChangedBombs() const;
		size_t getBombCount() const;
		void addBomb(BombState* bomb);
		void reduceAllBombsLifeTime(double time);
		std::vector<const ExplodedBombState*> getAllChangedExplodedBombs() const;
		std::vector<const BombState *> setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();
		void resetChangedFlags();
		void removeAllObjectsWithDestroyedFlag();
		unsigned int getHeight() const;
		unsigned int getWidth() const;
		std::vector<const BombState*> getAllBombsWithNoLifeTime() const;
		void eraseWallById(unsigned int wallId);
		void setBombsLifeTimeToZero(unsigned int bombId);
		std::vector<unsigned int> getAllPossiblePowerUpIDs() const;
		const PowerUpState* getPowerUpById(unsigned int powerUpId);
		void erasePowerUpById(unsigned int powerUpId);
		void addPowerUp(PowerUpState* powerUp);
		size_t getPowerUpCount() const;
		std::vector<const PowerUpState*> getAllChangedPowerUps() const;
		size_t getPlayerCount() const;
		void erasePlayerById(unsigned int playerId);
		std::vector<const BombState*> getAllBombsWithDestroyedFlag() const;
		std::vector<const WallState*> getAllWallsWithDestroyedFlag() const;
		std::vector<const PowerUpState*> getAllPowerUpsWithDestroyedFlag() const;
		size_t getExplodedBombCount() const;

	private:
		void eraseBomb(size_t position);
		void eraseWall(size_t position);
		void erasePowerUp(size_t position);
		void erasePlayer(size_t position);

	private:
		// forbid copies
		GameState(const GameState &rhs);
		void operator=(const GameState &rhs);

	private:
		std::vector<PlayerState*> m_players;
		std::vector<const PlayerState*> m_playersConst;
		std::vector<WallState*> m_walls;
		std::vector<BombState*> m_bombs;
		std::vector<PowerUpState*> m_powerUps;
		std::vector<ExplodedBombState*> m_explodedBombs;
		unsigned int m_height;
		unsigned int m_width;
	};
}

#endif
