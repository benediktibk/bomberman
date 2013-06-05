#ifndef COMMON_GAMESTATE_H
#define COMMON_GAMESTATE_H

#include "playerstate.h"
#include "wallstate.h"
#include "bombstate.h"
#include <vector>
#include "leveldefinition.h"
#include "uniqueidcreator.h"
#include "powerupstate.h"

namespace Common
{
class GameState
{
public:
    GameState(const LevelDefinition &level, UniqueIdCreator &creator );
    ~GameState();


    PlayerState& getPlayerState() ;
    PlayerState& getPlayerStateById(unsigned int playerId);
    const PlayerState& getPlayerState() const;
    std::vector<const WallState*> getAllChangedWalls() const;
    size_t getWallCount() const;
    void addWall(WallState* wall);
    std::vector<const BombState*> getAllChangedBombs() const;
    size_t getBombCount() const;
    void addBomb(BombState* bomb);
    void reduceAllBombsLifeTime(double time);
    void setAllBombsWithNoLifeTimeDestroyed(PlayerState &playerState);
    void resetChangedFlags();
    void removeAllObjectsWithDestroyedFlag();
    unsigned int getGameStateHeight() const;
    unsigned int getGameStateWidth() const;
    std::vector<const BombState*> getAllBombsWithNoLifeTime() const;
    void eraseWallById(unsigned int wallId);
    void setBombsLifeTimeToZero(unsigned int bombId);
    const PowerUpState* getPowerUpById(unsigned int powerUpId);
    void removePowerUpById(unsigned int powerUpId);
    void addPowerUp(PowerUpState* powerUp);
    size_t getPowerUpCount() const;
    std::vector<const PowerUpState*> getAllChangedPowerUps() const;

private:
    void eraseBomb(size_t position);
    void eraseWall(size_t position);
    void erasePowerUp(size_t position);

private:
    // forbid copies
    GameState(const GameState &rhsm, UniqueIdCreator &rhs);
    void operator=(const GameState &rhs);

private:
    std::vector<PlayerState*> m_players;
    std::vector<WallState*> m_walls;
    std::vector<BombState*> m_bombs;
    std::vector<PowerUpState*>m_powerUps;
    unsigned int m_height;
    unsigned int m_width;

};
}

#endif
