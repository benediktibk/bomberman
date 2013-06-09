#include "gamestate.h"
#include "playerstate.h"
#include <assert.h>

using namespace Common;
using namespace std;

GameState::GameState(const LevelDefinition &level, unsigned int playerCount, UniqueIdCreator &playerIDCreator, UniqueIdCreator &wallIDCreator) :
	m_height(level.getLevelHeight()),
	m_width(level.getLevelWidth())
{
	assert(playerCount > 0);

	for (unsigned int i = 0; i < playerCount; ++i)
	{
		PlayerState *player = new PlayerState(playerIDCreator);
		m_players.push_back(player);
		m_playersConst.push_back(player);
	}

    unsigned int playerPositionCount = 0;
	for(unsigned int x = 0; x < level.getLevelWidth(); x++)
	{
		for(unsigned int y = 0; y < level.getLevelHeight(); y++)
		{
			if(level.getObjectTypeAtPosition(x, y) == LevelDefinition::ObjectTypeSolidWall)
			{
				WallState *wallstate = new WallState(wallIDCreator, WallState::WallTypeSolid, Point(x, y));
				addWall(wallstate);
			}

			if(level.getObjectTypeAtPosition(x, y) == LevelDefinition::ObjectTypeLooseWall)
			{
				WallState *wallstate = new WallState(wallIDCreator, WallState::WallTypeLoose, Point(x, y));
				addWall(wallstate);
			}
            if(level.getObjectTypeAtPosition(x, y) == LevelDefinition::ObjectTypePlayer)
            {
                m_players[playerPositionCount]->setPosition(Point(x,y));
            }
		}
	}
}

GameState::~GameState()
{
	for(std::vector<BombState*>::iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
		delete *i;
	for(std::vector<WallState*>::iterator i = m_walls.begin(); i != m_walls.end(); ++i)
		delete *i;
	for(vector<PowerUpState*>::iterator i = m_powerUps.begin(); i != m_powerUps.end(); ++i)
		delete *i;
	for(vector<PlayerState*>::iterator i = m_players.begin(); i != m_players.end(); ++i)
		delete *i;

	m_bombs.clear();
	m_walls.clear();
	m_powerUps.clear();
	m_players.clear();
}

PlayerState &GameState::getFirstPlayerState()
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

const PlayerState &GameState::getPlayerStateById(unsigned int playerId) const
{
	for(size_t i = 0; i < m_players.size(); i++)
	{
		if((m_players[i]->getId() == playerId))
			return *(m_players[i]);
	}

   assert(false);
   return *(m_players[0]);
}

vector<unsigned int> GameState::getAllPossiblePlayerIDs() const
{
	vector<unsigned int> result;
	result.reserve(m_players.size());

	for (vector<PlayerState*>::const_iterator i = m_players.begin(); i != m_players.end(); ++i)
		result.push_back((*i)->getId());

	return result;
}

const std::vector<const PlayerState *> &GameState::getAllPlayers() const
{
	return m_playersConst;
}

const PlayerState &GameState::getFirstPlayerState() const
{
	return *(m_players[0]);
}

PlayerState &GameState::getSecondPlayerState()
{
	return *(m_players[1]);
}

const PlayerState &GameState::getSecondPlayerState() const
{
	return *(m_players[1]);
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

vector<const BombState*> GameState::setAllBombsWithNoLifeTimeDestroyed()
{
	vector<const BombState*> destroyedBombs;

	for(size_t i = 0; i < m_bombs.size(); i++)
	{
		BombState *currentBomb = m_bombs[i];
		if (currentBomb->getLifeTime() <= 0)
		{
			currentBomb->setDestroyed();
			destroyedBombs.push_back(currentBomb);
		}
	}

	return destroyedBombs;
}

void GameState::resetChangedFlags()
{
	for (vector<WallState*>::iterator i = m_walls.begin(); i != m_walls.end(); ++i)
		(*i)->resetChanged();
	for (vector<BombState*>::iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
		(*i)->resetChanged();
	for (vector<PowerUpState*>::iterator i = m_powerUps.begin(); i != m_powerUps.end(); ++i)
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

	for (size_t i = 0; i < m_powerUps.size(); ++i)
	{
		if (m_powerUps[i]->isDestroyed())
			erasePowerUp(i);
	}
    
    for (size_t i = 0; i < m_players.size(); ++i)
	{
		if (m_players[i]->isDestroyed())
			erasePlayer(i);
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

vector<const BombState*> GameState::getAllBombsWithNoLifeTime() const
{
	vector<const BombState*> result;

	for(size_t i = 0; i < m_bombs.size(); i++)
	{
	   BombState *currentBomb = m_bombs[i];
	   if (currentBomb->getLifeTime() <= 0)
		   result.push_back(currentBomb);
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
		if((m_bombs[i]->getID() == bombId))
			m_bombs[i]->setLifeTime(0);
	}
}

const PowerUpState* GameState::getPowerUpById(unsigned int powerUpId)
{
	for(size_t i = 0; i < m_powerUps.size(); i++)
	{
		if(m_powerUps[i]->getId() == powerUpId)
			return m_powerUps[i];
	}

	assert(false);
	return m_powerUps[0];
}

void GameState::erasePowerUpById(unsigned int powerUpId)
{
	for(size_t i = 0; i < m_powerUps.size(); i++)
	{
		if(m_powerUps[i]->getId() == powerUpId)
			m_powerUps[i]->setDestroyed();
	}
}

void GameState::addPowerUp(PowerUpState *powerUp)
{
	m_powerUps.push_back(powerUp);
}

void GameState::erasePowerUp(size_t position)
{
	delete m_powerUps[position];
	m_powerUps.erase(m_powerUps.begin() + position);
}

size_t GameState::getPowerUpCount() const
{
	return m_powerUps.size();
}

vector<const PowerUpState*> GameState::getAllChangedPowerUps() const
{
	vector<const PowerUpState*> result;
	result.reserve(m_powerUps.size());

	for (vector<PowerUpState*>::const_iterator i = m_powerUps.begin(); i != m_powerUps.end(); ++i)
		if ((*i)->hasChanged())
			result.push_back(*i);

	return result;
}

size_t GameState::getPlayerCount() const
{
	return m_players.size();
}

void GameState::erasePlayer(size_t position)
{
	delete m_players[position];
	m_players.erase(m_players.begin() + position);
}

void GameState::erasePlayerById(unsigned int playerId)
{
	for(size_t i = 0; i < m_players.size(); i++)
	{
		if(m_players[i]->getId() == playerId)
			m_players[i]->setDestroyed();
	}
}
