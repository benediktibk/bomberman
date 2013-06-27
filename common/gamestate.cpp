#include "common/gamestate.h"
#include "common/playerstate.h"
#include <assert.h>
#include <algorithm>

using namespace Common;
using namespace std;

GameState::GameState(const LevelDefinition &level, unsigned int humanPlayerCount, unsigned int computerEnemyCount, UniqueIdCreator &playerIDCreator, UniqueIdCreator &wallIDCreator) :
	m_height(level.getHeight()),
	m_width(level.getWidth()),
	m_originalHumanPlayerCount(humanPlayerCount),
	m_originalComputerEnemyCount(computerEnemyCount)
{
	unsigned int playerCount = humanPlayerCount + computerEnemyCount;
	assert(playerCount > 0);
	assert(playerCount <= level.getPlayerStartPositionCount());

	for (unsigned int i = 0; i < playerCount; ++i)
	{
		PlayerState *player = new PlayerState(playerIDCreator);
		m_players.push_back(player);
		m_playersConst.push_back(player);
	}

	unsigned int playerPositionCount = 0;
	for(unsigned int x = 0; x < level.getWidth(); x++)
	{
		for(unsigned int y = 0; y < level.getHeight(); y++)
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
				if (playerPositionCount < playerCount)
				{
					m_players[playerPositionCount]->setPosition(Point(x,y));
					playerPositionCount++;
				}
			}
		}
	}

	vector<unsigned int> allPlayerIDs = getAllNotDestroyedPlayerIDs();
	for (unsigned int i = 0; i < humanPlayerCount; ++i)
		m_originalHumanPlayerIDs.push_back(allPlayerIDs[i]);
	for (unsigned int i = humanPlayerCount; i < playerCount; ++i)
		m_originalComputerEnemyIDs.push_back(allPlayerIDs[i]);
	assert(m_originalHumanPlayerIDs.size() == humanPlayerCount);
	assert(m_originalComputerEnemyIDs.size() == computerEnemyCount);
	assert(allPlayerIDs.size() == playerCount);
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
	for (vector<ExplodedBombState*>::iterator i = m_explodedBombs.begin(); i != m_explodedBombs.end(); ++i)
		delete *i;

	m_bombs.clear();
	m_walls.clear();
	m_powerUps.clear();
	m_players.clear();
	m_explodedBombs.clear();
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

vector<unsigned int> GameState::getAllNotDestroyedPlayerIDs() const
{
	vector<unsigned int> result;
	result.reserve(m_players.size());

	for (vector<PlayerState*>::const_iterator i = m_players.begin(); i != m_players.end(); ++i)
		result.push_back((*i)->getId());

	return result;
}

vector<unsigned int> GameState::getAllNotDestroyedHumanPlayerIDs() const
{
	vector<unsigned int> allPlayerIDs = getAllNotDestroyedPlayerIDs();
	vector<unsigned int> result;

	for (vector<unsigned int>::const_iterator i = allPlayerIDs.begin(); i != allPlayerIDs.end(); ++i)
		if (count(m_originalHumanPlayerIDs.begin(), m_originalHumanPlayerIDs.end(), *i) == 1)
			result.push_back(*i);

	return result;
}

vector<unsigned int> GameState::getAllNotDestroyedComputerEnemyIDs() const
{
	vector<unsigned int> allPlayerIDs = getAllNotDestroyedPlayerIDs();
	vector<unsigned int> result;

	for (vector<unsigned int>::const_iterator i = allPlayerIDs.begin(); i != allPlayerIDs.end(); ++i)
		if (count(m_originalComputerEnemyIDs.begin(), m_originalComputerEnemyIDs.end(), *i) == 1)
			result.push_back(*i);

	return result;
}

bool GameState::isHumanPlayerID(unsigned int playerID) const
{
	if (count(m_originalHumanPlayerIDs.begin(), m_originalHumanPlayerIDs.end(), playerID) == 1)
		return true;
	else
	{
		assert(count(m_originalComputerEnemyIDs.begin(), m_originalComputerEnemyIDs.end(), playerID) == 1);
		return false;
	}
}

unsigned int GameState::getIndexOfHumanPlayer(unsigned int playerID) const
{
	assert(isHumanPlayerID(playerID));
	vector<unsigned int>::const_iterator position = find(m_originalHumanPlayerIDs.begin(), m_originalHumanPlayerIDs.end(), playerID);
	return position - m_originalHumanPlayerIDs.begin();
}

unsigned int GameState::getIndexOfComputerEnemy(unsigned int playerID) const
{
	assert(!isHumanPlayerID(playerID));
	vector<unsigned int>::const_iterator position = find(m_originalComputerEnemyIDs.begin(), m_originalComputerEnemyIDs.end(), playerID);
	return position - m_originalComputerEnemyIDs.begin();
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
	assert(m_players.size() > 1);
	return *(m_players[1]);
}

const PlayerState &GameState::getSecondPlayerState() const
{
	assert(m_players.size() > 1);
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

const WallState& GameState::getWallById(unsigned int id) const
{
	for (vector<WallState*>::const_iterator i = m_walls.begin(); i != m_walls.end(); ++i)
		if (id == (*i)->getId())
			return **i;

	assert(false);
	return *(m_walls.front());
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

const BombState &GameState::getBombById(unsigned int id) const
{
	for (vector<BombState*>::const_iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
		if (id == (*i)->getID())
			return **i;

	assert(false);
	return *(m_bombs.front());
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
	for (size_t i = 0; i < m_bombs.size(); i++)
	{
		BombState *currentBomb = m_bombs[i];
		currentBomb->setLifeTime(currentBomb->getLifeTime() - time);
	}

	for (vector<ExplodedBombState*>::iterator i = m_explodedBombs.begin(); i != m_explodedBombs.end(); ++i)
		(*i)->decreaseLifeTime(time);
}

vector<const ExplodedBombState*> GameState::getAllChangedExplodedBombs() const
{
	vector<const ExplodedBombState*> result;

	for (vector<ExplodedBombState*>::const_iterator i = m_explodedBombs.begin(); i != m_explodedBombs.end(); ++i)
		if ((*i)->hasChanged())
			result.push_back(*i);

	return result;
}

vector<const BombState*> GameState::setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs()
{
	vector<const BombState*> destroyedBombs;

	for(size_t i = 0; i < m_bombs.size(); i++)
	{
		BombState *currentBomb = m_bombs[i];

		if (currentBomb->getLifeTime() <= 0)
		{
			ExplodedBombState *explodedBomb = new ExplodedBombState(*currentBomb);
			currentBomb->setDestroyed();
			destroyedBombs.push_back(currentBomb);
			m_explodedBombs.push_back(explodedBomb);
			m_bombToExplodedBomb.insert(pair<BombState*, ExplodedBombState*>(currentBomb, explodedBomb));
			m_explodedBombToBomb.insert(pair<ExplodedBombState*, BombState*>(explodedBomb, currentBomb));
		}
	}

	for (vector<ExplodedBombState*>::iterator i = m_explodedBombs.begin(); i != m_explodedBombs.end(); ++i)
		(*i)->setDestroyedIfNoLifeTimeLeft();

	return destroyedBombs;
}

ExplodedBombState& GameState::getExplodedBombByBomb(const BombState *bomb)
{
	assert(m_bombToExplodedBomb.find(bomb) != m_bombToExplodedBomb.end());

	return *(m_bombToExplodedBomb[bomb]);
}

void GameState::resetChangedFlags()
{
	for (vector<WallState*>::iterator i = m_walls.begin(); i != m_walls.end(); ++i)
		(*i)->resetChanged();
	for (vector<BombState*>::iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
		(*i)->resetChanged();
	for (vector<PowerUpState*>::iterator i = m_powerUps.begin(); i != m_powerUps.end(); ++i)
		(*i)->resetChanged();
	for (vector<ExplodedBombState*>::iterator i = m_explodedBombs.begin(); i != m_explodedBombs.end(); ++i)
		(*i)->resetChanged();
}

void GameState::removeAllObjectsWithDestroyedFlag()
{
	size_t i = 0;
	while (i < m_walls.size())
	{
		if (m_walls[i]->isDestroyed())
			eraseWall(i);
		else
			i++;
	}

	i = 0;
	while (i < m_bombs.size())
	{
		if (m_bombs[i]->isDestroyed())
			eraseBomb(i);
		else
			i++;
	}

	i = 0;
	while (i < m_powerUps.size())
	{
		if (m_powerUps[i]->isDestroyed())
			erasePowerUp(i);
		else
			i++;
	}

	i = 0;
	while (i < m_players.size())
	{
		if (m_players[i]->isDestroyed())
			erasePlayer(i);
		else
			i++;
	}

	i = 0;
	while (i < m_explodedBombs.size())
	{
		if (m_explodedBombs[i]->isDestroyed())
		{
			ExplodedBombState *explodedBomb = m_explodedBombs[i];
			map<const ExplodedBombState*, const BombState*>::iterator explodedBombToBomb = m_explodedBombToBomb.find(explodedBomb);
			assert(explodedBombToBomb != m_explodedBombToBomb.end());
			map<const BombState*, ExplodedBombState*>::iterator bombToExplodedBomb = m_bombToExplodedBomb.find(explodedBombToBomb->second);
			assert(bombToExplodedBomb != m_bombToExplodedBomb.end());
			m_explodedBombToBomb.erase(explodedBombToBomb);
			m_bombToExplodedBomb.erase(bombToExplodedBomb);

			delete explodedBomb;
			m_explodedBombs.erase(m_explodedBombs.begin() + i);
		}
		else
			++i;
	}
}

unsigned int GameState::getHeight() const
{
	return m_height;
}

unsigned int GameState::getWidth() const
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

void GameState::setBombsLifeTimeToZeroIfPositive(unsigned int bombId)
{
	for(size_t i = 0; i < m_bombs.size(); i++)
	{
		if(m_bombs[i]->getID() == bombId && m_bombs[i]->getLifeTime() >= 0)
			m_bombs[i]->setLifeTime(0);
	}
}

vector<unsigned int> GameState::getAllPossiblePowerUpIDs()const
{
	vector<unsigned int> result;
	result.reserve(m_powerUps.size());

	for (vector<PowerUpState*>::const_iterator i = m_powerUps.begin(); i != m_powerUps.end(); ++i)
		result.push_back((*i)->getId());

	return result;
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
	m_playersConst.erase(m_playersConst.begin() + position);
}

void GameState::erasePlayerById(unsigned int playerId)
{
	for(size_t i = 0; i < m_players.size(); i++)
	{
		if(m_players[i]->getId() == playerId)
			m_players[i]->setDestroyed();
	}
}

vector<const BombState*> GameState::getAllBombsWithDestroyedFlag() const
{
	vector<const BombState*> result;

	for (vector<BombState*>::const_iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
		if ((*i)->isDestroyed())
			result.push_back(*i);

	return result;
}

vector<const WallState*> GameState::getAllWallsWithDestroyedFlag() const
{
	vector<const WallState*> result;

	for (vector<WallState*>::const_iterator i = m_walls.begin(); i != m_walls.end(); ++i)
		if ((*i)->isDestroyed())
			result.push_back(*i);

	return result;
}

vector<const PowerUpState*> GameState::getAllPowerUpsWithDestroyedFlag() const
{
	vector<const PowerUpState*> result;

	for (vector<PowerUpState*>::const_iterator i = m_powerUps.begin(); i != m_powerUps.end(); ++i)
		if ((*i)->isDestroyed())
			result.push_back(*i);

	return result;
}

size_t GameState::getExplodedBombCount() const
{
	return m_explodedBombs.size();
}

bool GameState::isPlayerAlive(unsigned int playerId) const
{
	for(size_t i = 0; i < m_players.size(); i++)
	{
		if(m_players[i]->getId() == playerId && !m_players[i]->isDestroyed())
			return true;
	}

	return false;
}
