#include "gamestate.h"

using namespace Common;
using namespace std;

GameState::GameState()
{ }

GameState::~GameState()
{
    for(std::vector<BombState*>::iterator i = m_bombs.begin();i != m_bombs.end(); ++i)
    {
        delete *i;
    }
    for(std::vector<WallState*>::iterator i = m_walls.begin();i != m_walls.end(); ++i)
    {
        delete *i;
    }
}

void GameState::setPlayerState(const PlayerState &state)
{
	m_playerState = state;
}

const PlayerState &GameState::getPlayerState() const
{
	return m_playerState;
}

const vector<WallState*> &GameState::getAllWalls() const
{
	return m_walls;
}

void GameState::addWall(WallState* wall)
{
	m_walls.push_back(wall);
}

const vector<BombState*> &GameState::getAllBombs() const
{
	return m_bombs;
}

void GameState::addBomb(BombState* bomb)
{
    m_bombs.push_back(bomb);
}

void GameState::eraseBomb(int position)
{
    delete m_bombs[position];
    m_bombs.erase(m_bombs.begin()+position);
}

GameState::GameState(const GameState &)
{ }

void GameState::operator=(const GameState &)
{ }
