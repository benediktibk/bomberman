#ifndef COMMON_GAMESTATE_H
#define COMMON_GAMESTATE_H

#include "playerstate.h"
#include "wallstate.h"
#include "bombstate.h"
#include <vector>
#include "leveldefinition.h"
#include "uniqueidcreator.h"

namespace Common
{
class GameState
{
public:
    GameState(const LevelDefinition &level, UniqueIdCreator &creator );
    ~GameState();


    PlayerState& getPlayerState() ;
    const PlayerState& getPlayerState() const;
    std::vector<const WallState*> getAllChangedWalls() const;
    size_t getWallCount() const;
    void addWall(WallState* wall);
    std::vector<const BombState*> getAllChangedBombs() const;
    size_t getBombCount() const;
    void addBomb(BombState* bomb);
    void reduceAllBombsLifeTime(double time);
    void setAllBombsWithNegativeLifeTimeDestroyed(PlayerState &playerState);
    void resetChangedFlags();
    void removeAllObjectsWithDestroyedFlag();
    unsigned int getGameStateHeight() const;
    unsigned int getGameStateWidth() const;
    std::vector<const BombState*> getAllBombsWithNegativeLifeTime() const;
    void eraseWallById(unsigned int wallId);
    void setBombsLifeTimeToZero(unsigned int bombId);
    
private:
    void eraseBomb(size_t position);
    void eraseWall(size_t position);

private:
    // forbid copies
    GameState(const GameState &rhsm, UniqueIdCreator &rhs);
    void operator=(const GameState &rhs);

private:
    PlayerState m_playerState;
    std::vector<WallState*> m_walls;
    std::vector<BombState*> m_bombs;
    unsigned int m_height;
    unsigned int m_width;

};
}

#endif
