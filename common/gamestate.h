#ifndef COMMON_GAMESTATE_H
#define COMMON_GAMESTATE_H

#include "playerstate.h"
#include "wallstate.h"
#include "bombstate.h"
#include <vector>

namespace Common
{
class GameState
{
public:
	GameState();
	~GameState();

	void setPlayerState(const PlayerState &state);
	const PlayerState& getPlayerState() const;
	std::vector<const WallState*> getAllChangedWalls() const;
	size_t getWallCount() const;
	void addWall(WallState* wall);
	std::vector<const BombState*> getAllChangedBombs() const;
	size_t getBombCount() const;
	void addBomb(BombState* bomb);
	void reduceAllBombsLifeTime(double time);
	void deleteAllBombsWithNegativeLifeTime(PlayerState &playerState);
	void resetChangedFlags();
	void removeAllObjectsWithDestroyedFlag();

private:
	void eraseBomb(size_t position);
	void eraseWall(size_t position);

private:
	// forbid copies
	GameState(const GameState &rhs);
	void operator=(const GameState &rhs);

private:
	PlayerState m_playerState;
	std::vector<WallState*> m_walls;
	std::vector<BombState*> m_bombs;

};
}

#endif
