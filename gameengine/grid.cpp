#include "grid.h"
#include <assert.h>

using namespace Common;
using namespace GameEngine;
using namespace std;

Grid::Grid(unsigned int rows,unsigned int cols) :
	m_gridRows(rows),
	m_gridColumns(cols),
	m_numberOfItems(m_gridColumns*m_gridRows),
	m_itemMatrix(m_numberOfItems,ItemFree),
	m_idMatrix(m_numberOfItems,0)
{ }

bool Grid::isPlaceEmpty(const Point &position) const
{
	GridPoint gridPosition(position);
	unsigned int index = getVectorIndex(gridPosition);
	if(m_itemMatrix[index] == ItemFree)
		return true;
	else
		return false;
}

bool Grid::isPlaceEmpty(const GridPoint &position) const
{
	unsigned int index = getVectorIndex(position);
	if(m_itemMatrix[index] == ItemFree)
		return true;
	else
		return false;
}

void Grid::addBombAtPlace(BombState &bomb)
{
	GridPoint position(bomb.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemBomb;
	m_idMatrix[index] = bomb.getBombId();
	bomb.setPosition(position.getPointPosition());
}

void Grid::addWallAtPlace(WallState &wall)
{
	GridPoint position(wall.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemWall;
	m_idMatrix[index] = wall.getId();
}

void Grid::addPowerUpAtPlace(PowerUpState &powerUp)
{
    GridPoint position(powerUp.getPosition());
    unsigned int index = getVectorIndex(position);
    m_itemMatrix[index] = ItemPowerUp;
    m_idMatrix[index] = powerUp.getId();
}

void Grid::removePowerUp(PowerUpState &powerUp)
{
    GridPoint position(powerUp.getPosition());
    unsigned int index = getVectorIndex(position);
    m_itemMatrix[index] = ItemFree;
    m_idMatrix[index] = 0;
}

void Grid::removeBomb(BombState &bomb)
{
	GridPoint position(bomb.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;
}

void Grid::removeWall(WallState &wall)
{
	GridPoint position(wall.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;
 }

void Grid::updatePlayer(const PlayerState &player)
{
	GridPoint position(player.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemPlayer;
	//m_idMatrix[index] = player.getPlayerId;
}

vector<unsigned int> Grid::getItemsInRange(const BombState &bomb , Grid::Item item) const
{
    vector<unsigned int> itemsInRange;
    GridPoint position(bomb.getPosition());
    int x = position.getX();
    int y = position.getY();
    int range =bomb.getDestructionRange();
    bool isWallRight = false;
    bool isWallLeft = false;
    bool isWallUp = false;
    bool isWallDown = false;
    for( int i=1 ; i<=range ; ++i)
    {
        if((x+i)<static_cast<int>(m_gridRows))
        {
            if (m_itemMatrix[getVectorIndex(x+i,y)] == item && isWallRight == false)
            {
                if(m_itemMatrix[getVectorIndex(x+i-1,y)] == ItemWall)
                    isWallRight = true;
                else
                    itemsInRange.push_back(m_idMatrix[getVectorIndex(x+i,y)]);
            }
        }
        if((x-i)>=0)
        {
            if (m_itemMatrix[getVectorIndex(x-i,y)] == item && isWallLeft == false)
            {
                if(m_itemMatrix[getVectorIndex(x-i+1,y)] == ItemWall)
                    isWallLeft = true;
                else
                    itemsInRange.push_back(m_idMatrix[getVectorIndex(x-i,y)]);
            }
        }
        if((y+i)<static_cast<int>(m_gridColumns))
        {
            if (m_itemMatrix[getVectorIndex(x,y+i)] == item && isWallUp == false)
            {
                if(m_itemMatrix[getVectorIndex(x,y+i-1)] == ItemWall)
                    isWallUp = true;
                else
                    itemsInRange.push_back(m_idMatrix[getVectorIndex(x,y+i)]);
            }
        }
        if((y-i)>=0)
        {
            if (m_itemMatrix[getVectorIndex(x,y-i)] == item && isWallDown == false)
            {
                if(m_itemMatrix[getVectorIndex(x,y-i+1)] == ItemWall)
                    isWallDown = true;
                else
                    itemsInRange.push_back(m_idMatrix[getVectorIndex(x,y-i)]);
            }
        }
    }
    return itemsInRange;
}

vector<unsigned int> Grid::getWallsInRange(const BombState &bomb) const
{
    vector<unsigned int> result = getItemsInRange(bomb , ItemWall);
    return result;
}

vector<unsigned int> Grid::getPlayersInRange(const BombState &bomb) const
{
    vector<unsigned int> result = getItemsInRange(bomb , ItemPlayer);
    return result;
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
	assert(x < m_gridColumns);
	assert(y < m_gridRows);
	unsigned int index = m_gridColumns*y+x;
	return index;
}

vector<GridPoint> Grid::getPlayerFields(const Common::PlayerState &player) const
{
    Point position = player.getPosition();
    GridPoint positionGrid(position);
    vector<GridPoint> result;
// Should be a coorect implementation Player doesnt move anymore though
//    double x = position.getX();
//    double y = position.getY();
//    double xGrid = positionGrid.getX();
//    double yGrid = positionGrid.getY();
//
//    if ((x-xGrid)>0)
//    {
//        result.push_back(positionGrid);
//        GridPoint positionGrid2(positionGrid.getX()+1,positionGrid.getY());
//        result.push_back(positionGrid2);
//    }
//    if ((y-yGrid)>0)
//    {
//        result.push_back(positionGrid);
//        GridPoint positionGrid2(positionGrid.getX(),positionGrid.getY()+1);
//        result.push_back(positionGrid2);
//    }
//    if((x-xGrid) == 0 && (y-yGrid) == 0 )
//    {
//        result.push_back(positionGrid);
//    }

    result.push_back(positionGrid);
	return result;
}
