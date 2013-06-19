#include "grid.h"
#include <assert.h>
#include <math.h>

using namespace Common;
using namespace GameEngine;
using namespace std;

Grid::Grid(unsigned int rows, unsigned int cols) :
	m_gridRows(rows),
	m_gridColumns(cols),
	m_numberOfItems(m_gridColumns*m_gridRows),
	m_itemMatrix(m_numberOfItems,ItemFree),
	m_idMatrix(m_numberOfItems,0)
{ }

bool Grid::isPlaceEmpty(const Point &position) const
{
	GridPoint gridPosition(position);
	return isPlaceEmpty(gridPosition);
}

bool Grid::isPlaceEmpty(const GridPoint &position) const
{
	unsigned int index = getVectorIndex(position);
	if(m_itemMatrix[index] == ItemFree)
		return true;
	else
		return false;
}

bool Grid::isPlaceCoveredByWall(const GridPoint &position) const
{
	unsigned int index = getVectorIndex(position);
	return m_itemMatrix[index] == ItemSolidWall || m_itemMatrix[index] == ItemLooseWall;
}

unsigned Grid::getId(const GridPoint &position) const
{
	assert(!isPlaceEmpty(position));
	return m_idMatrix[getVectorIndex(position)];
}

void Grid::addBombAtPlace(BombState &bomb)
{
	GridPoint position(bomb.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemBomb;
	m_idMatrix[index] = bomb.getID();
	bomb.setPosition(position.getPointPosition());
}

void Grid::addWallAtPlace(const WallState &wall)
{
	GridPoint position(wall.getPosition());
	unsigned int index = getVectorIndex(position);

	if (WallState::WallTypeSolid == wall.getWallType())
		m_itemMatrix[index] = ItemSolidWall;
	else
		m_itemMatrix[index] = ItemLooseWall;

	m_idMatrix[index] = wall.getId();
}

void Grid::addPowerUpAtPlace(PowerUpState &powerUp)
{
	GridPoint position(powerUp.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemPowerUp;
	m_idMatrix[index] = powerUp.getId();
}

void Grid::removePowerUp(const PowerUpState &powerUp)
{
	GridPoint position(powerUp.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;
}

void Grid::removeBomb(const BombState &bomb)
{
	GridPoint position(bomb.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;
}

void Grid::removeWall(const WallState &wall)
{
	GridPoint position(wall.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;
 }

void Grid::removePlayer(const PlayerState &player)
{
	GridPoint position(player.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemPlayer;
	m_idMatrix[index] = 0;
}

void Grid::updatePlayer(const PlayerState &player)
{
	GridPoint position(player.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemPlayer;
	m_idMatrix[index] = player.getId();
}

vector<unsigned int> Grid::getItemsInRange(const BombState &bomb, Grid::Item item) const
{
	vector<unsigned int> itemsInRange;
	GridPoint position(bomb.getPosition());
	int x = position.getX();
	int y = position.getY();
	int range = bomb.getDestructionRange();
	bool isWallRightReached = false;
	bool isWallLeftReached = false;
	bool isWallUpReached = false;
	bool isWallDownReached = false;

	for(int i = 1 ; i <= range ; ++i)
	{
		if((x + i) < static_cast<int>(m_gridColumns))
		{
			if (m_itemMatrix[getVectorIndex(x + i, y)] == item && !isWallRightReached)
				itemsInRange.push_back(m_idMatrix[getVectorIndex(x + i, y)]);

			if(isPlaceCoveredByWall(GridPoint(x + i, y)))
				isWallRightReached = true;
		}

		if((x - i) >= 0)
		{
			if (m_itemMatrix[getVectorIndex(x - i, y)] == item && !isWallLeftReached)
				itemsInRange.push_back(m_idMatrix[getVectorIndex(x - i, y)]);

			if(isPlaceCoveredByWall(GridPoint(x - i, y)))
				isWallLeftReached = true;
		}

		if((y + i) < static_cast<int>(m_gridRows))
		{
			if (m_itemMatrix[getVectorIndex(x, y + i)] == item && !isWallUpReached)
				itemsInRange.push_back(m_idMatrix[getVectorIndex(x, y + i)]);

			if(isPlaceCoveredByWall(GridPoint(x, y + i)))
				isWallUpReached = true;
		}

		if((y - i) >= 0)
		{
			if (m_itemMatrix[getVectorIndex(x, y - i)] == item && !isWallDownReached)
				itemsInRange.push_back(m_idMatrix[getVectorIndex(x, y - i)]);

			if(isPlaceCoveredByWall(GridPoint(x, y - i)))
				isWallDownReached = true;
		}
	}

	return itemsInRange;
}

vector<unsigned int> Grid::getLooseWallsInRange(const BombState &bomb) const
{
	return getItemsInRange(bomb, ItemLooseWall);
}

vector<unsigned int> Grid::getPlayersInRange(const BombState &bomb) const
{
	return getItemsInRange(bomb, ItemPlayer);
}

vector<unsigned int> Grid::getBombsInRange(const BombState &bomb) const
{
	return getItemsInRange(bomb, ItemBomb);
}

vector<unsigned int> Grid::getPowerUpsInRange(const BombState &bomb) const
{
	return getItemsInRange(bomb, ItemPowerUp);
}

unsigned int Grid::getVectorIndex(const GridPoint &position) const
{
	assert(position.getX() < m_gridColumns);
	assert(position.getY() < m_gridRows);
	unsigned int x = position.getX();
	unsigned int y = position.getY();
	unsigned int index = m_gridColumns*y+x;
	return index;
}

unsigned int Grid::getVectorIndex(unsigned int x,unsigned int y) const
{
	assert(x< m_gridColumns);
	assert(y< m_gridRows);
	unsigned int index = m_gridColumns*y+x;
	return index;
}

vector<GridPoint> Grid::getPlayerFields(const Common::PlayerState &player) const
{
	Point position = player.getPosition();
	vector<GridPoint> fields = GridPoint::getCoveredGridPoints(position);
	return fields;
}

std::vector<unsigned int> Grid::getPlayersInRange(const BombState &bomb, std::vector<const PlayerState*> allPlayers) const
{
	std::vector<unsigned int> playersInRange;
	GridPoint position(bomb.getPosition());
	int x = position.getX();
	int y = position.getY();
	int range = bomb.getDestructionRange();
	bool isWallRight = false;
	bool isWallLeft = false;
	bool isWallUp = false;
	bool isWallDown = false;
	for( int i=1 ; i<=range ; ++i)
	{
		for(size_t p = 0; p < allPlayers.size(); p++)
		{
			GridPoint playerMainPosition(allPlayers[p]->getCenterPosition());
			int playerX = playerMainPosition.getX();
			int playerY = playerMainPosition.getY();

			if((x+i) < static_cast<int>(m_gridColumns))
			{
				if (isWallRight == false)
				{
					if(m_itemMatrix[getVectorIndex(x+i-1,y)] == ItemSolidWall)
						isWallRight = true;
					else if ((x+i) == playerX)
					{
						playersInRange.push_back(allPlayers[p]->getId());
					}
				}
			}
			if((x-i) >= 0)
			{
				if (isWallLeft == false)
				{
					if(m_itemMatrix[getVectorIndex(x-i+1,y)] == ItemSolidWall)
						isWallLeft = true;
					else  if ((x-i) == playerX)
					{
						playersInRange.push_back(allPlayers[p]->getId());
					}
				}
			}
			if((y+i) < static_cast<int>(m_gridRows))
			{
				if (isWallUp == false)
				{
					if(m_itemMatrix[getVectorIndex(x,y+i-1)] == ItemSolidWall)
						isWallUp = true;
					else  if ((y+i) == playerY)
					{
						playersInRange.push_back(allPlayers[p]->getId());
					}
				}
			}
			if((y-i) >= 0)
			{
				if (isWallDown == false)
				{
					if(m_itemMatrix[getVectorIndex(x,y-i+1)] == ItemSolidWall)
						isWallDown = true;
					else if ((y-i) == playerY)
					{
						playersInRange.push_back(allPlayers[p]->getId());
					}
				}
			}
		}
	}

	return playersInRange;
}

unsigned int Grid::getDistanceToNextWallLeft(const GridPoint &position) const
{
	unsigned int distance;

	for (distance = 1; position.getX() - distance < m_gridColumns; ++distance)
		if (isPlaceCoveredByWall(position - GridPoint(distance, 0)))
			return distance - 1;

	return distance - 1;
}

unsigned int Grid::getDistanceToNextWallRight(const GridPoint &position) const
{
	unsigned int distance;

	for (distance = 1; position.getX() + distance < m_gridColumns; ++distance)
		if (isPlaceCoveredByWall(position + GridPoint(distance, 0)))
			return distance - 1;

	return distance - 1;
}

unsigned int Grid::getDistanceToNextWallUp(const GridPoint &position) const
{
	unsigned int distance;

	for (distance = 1; position.getY() + distance < m_gridRows; ++distance)
		if (isPlaceCoveredByWall(position + GridPoint(0, distance)))
			return distance - 1;

	return distance - 1;
}

unsigned int Grid::getDistanceToNextWallDown(const GridPoint &position) const
{
	unsigned int distance;

	for (distance = 1; position.getY() - distance < m_gridRows; ++distance)
		if (isPlaceCoveredByWall(position - GridPoint(0, distance)))
			return distance - 1;

	return distance - 1;
}
