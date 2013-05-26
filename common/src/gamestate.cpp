#include "gamestate.h"

using namespace Common;
using namespace std;

void GameState::setPlayerState(const PlayerState &state)
{
	m_playerState = state;
}

const PlayerState &GameState::getPlayerState() const
{
	return m_playerState;
}

const vector<WallState> &GameState::getAllWalls() const
{
	return m_walls;
}

void GameState::addWall(const WallState &wall)
{
	m_walls.push_back(wall);
}

const vector<BombState> &GameState::getAllBombs() const
{
	return m_bombs;
}

void GameState::addBomb(const BombState &bomb)
{
	m_bombs.push_back(bomb);
}

void GameState::eraseBomb(int position)
{
    m_bombs.erase(m_bombs.begin()+position);
}
