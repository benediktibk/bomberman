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
	const std::vector<BombState*> &getAllBombs() const;
	std::vector<const BombState*> getAllChangedBombs() const;
	size_t getBombCount() const;
	void addBomb(BombState* bomb);
	void eraseBomb(int position);

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
