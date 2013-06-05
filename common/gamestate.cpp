#include "gamestate.h"
#include "playerstate.h"
#include <assert.h>

using namespace Common;
using namespace std;

GameState::GameState(const LevelDefinition &level, UniqueIdCreator &creator) :
    m_height(level.getLevelHeight()),
    m_width(level.getLevelWidth())
{
    m_players.push_back(new PlayerState(creator));
}

GameState::~GameState()
{
    for(std::vector<BombState*>::iterator i = m_bombs.begin();i != m_bombs.end(); ++i)
        delete *i;
    for(std::vector<WallState*>::iterator i = m_walls.begin();i != m_walls.end(); ++i)
        delete *i;
}

PlayerState &GameState::getPlayerState()
{
    return *(m_players[0]);
}

PlayerState &GameState::getPlayerStateById(unsigned int playerId)
{
    for(size_t i = 0; i < m_players.size(); i++)
    {
        if((m_players[i]->getId() == playerId))
            return *(m_players[i]);
    }
   assert(false);
   return *(m_players[0]);
}

const PlayerState &GameState::getPlayerState() const
{
    return *(m_players[0]);
}

vector<const WallState*> GameState::getAllChangedWalls() const
{
    vector<const WallState*> result;
    result.reserve(m_walls.size());

    for (vector<WallState*>::const_iterator i = m_walls.begin(); i != m_walls.end(); ++i)
        if ((*i)->hasChanged())
            result.push_back(*i);

    return result;
}

size_t GameState::getWallCount() const
{
    return m_walls.size();
}

void GameState::addWall(WallState* wall)
{
    m_walls.push_back(wall);
}

vector<const BombState*> GameState::getAllChangedBombs() const
{
    vector<const BombState*> result;

    for (vector<BombState*>::const_iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
        if ((*i)->hasChanged())
            result.push_back(*i);

    return result;
}

size_t GameState::getBombCount() const
{
    return m_bombs.size();
}

void GameState::addBomb(BombState* bomb)
{
    m_bombs.push_back(bomb);
}

void GameState::eraseBomb(size_t position)
{
    delete m_bombs[position];
    m_bombs.erase(m_bombs.begin() + position);
}

void GameState::eraseWall(size_t position)
{
    delete m_walls[position];
    m_walls.erase(m_walls.begin() + position);
}

void GameState::reduceAllBombsLifeTime(double time)
{
    for(size_t i = 0; i < m_bombs.size(); i++)
    {
        BombState *currentBomb = m_bombs[i];
        currentBomb->setLifeTime(currentBomb->getLifeTime() - time);
    }
}

 void GameState::setAllBombsWithNoLifeTimeDestroyed(PlayerState &playerState)
 {
     for(size_t i = 0; i < m_bombs.size(); i++)
     {
        BombState *currentBomb = m_bombs[i];
        if (currentBomb->getLifeTime() <= 0)
        {
            currentBomb->setDestroyed();
            playerState.reduceBombCount();
        }
     }
 }

 void GameState::resetChangedFlags()
 {
     for (vector<WallState*>::iterator i = m_walls.begin(); i != m_walls.end(); ++i)
         (*i)->resetChanged();
     for (vector<BombState*>::iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
         (*i)->resetChanged();
 }

 void GameState::removeAllObjectsWithDestroyedFlag()
 {
     for (size_t i = 0; i < m_walls.size(); ++i)
     {
         if (m_walls[i]->isDestroyed())
             eraseWall(i);
     }

     for (size_t i = 0; i < m_bombs.size(); ++i)
     {
         if (m_bombs[i]->isDestroyed())
             eraseBomb(i);
     }
 }

 unsigned int GameState::getGameStateHeight() const
 {
     return m_height;
 }

 unsigned int GameState::getGameStateWidth() const
 {
     return m_width;
 }

 GameState::GameState(const GameState &, UniqueIdCreator &rhs)
 {
     m_players.push_back(new PlayerState(rhs));
 }

void GameState::operator=(const GameState &)
{ }

vector<const BombState*> GameState::getAllBombsWithNoLifeTime() const
{
    vector<const BombState*> result;

    for(size_t i = 0; i < m_bombs.size(); i++)
    {
       BombState *currentBomb = m_bombs[i];
       if (currentBomb->getLifeTime() < 0)
       {
           result.push_back(currentBomb);
       }
    }

    return result;
}

void GameState::eraseWallById(unsigned int wallId)
{
    for(size_t i = 0; i < m_walls.size(); i++)
    {
        if((m_walls[i]->getId() == wallId) && (m_walls[i]->getWallType() == WallState::WallTypeLoose) )
            m_walls[i]->setDestroyed();
    }
}

void GameState::setBombsLifeTimeToZero(unsigned int bombId)
{
    for(size_t i = 0; i < m_bombs.size(); i++)
    {
        if((m_bombs[i]->getBombId() == bombId))
            m_bombs[i]->setLifeTime(0);
    }
}
