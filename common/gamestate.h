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
	void setPlayerState(const PlayerState &state);
	const PlayerState& getPlayerState() const;
	const std::vector<WallState>& getAllWalls() const;
	void addWall(const WallState &wall);
	const std::vector<BombState> &getAllBombs() const;
	void addBomb(const BombState &bomb);
	void eraseBomb(int position);

private:
	PlayerState m_playerState;
	std::vector<WallState> m_walls;
	std::vector<BombState> m_bombs;
};
}

#endif
