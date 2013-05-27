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
	const std::vector<WallState>& getAllWalls() const;
	void addWall(const WallState &wall);
    const std::vector<BombState*> &getAllBombs() const;
    void addBomb(BombState* bomb);
	void eraseBomb(int position);

private:
    // forbid copies
    GameState(const GameState &rhs);
    void operator=(const GameState &rhs);

private:
	PlayerState m_playerState;
	std::vector<WallState> m_walls;
    std::vector<BombState*> m_bombs;
};
}

#endif
