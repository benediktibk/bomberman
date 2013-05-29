#include "grid.h"
#include<assert.h>

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
	unsigned int index = getVectorIndex(position);
	if(m_itemMatrix[index] == ItemFree)
		return true;
	else
		return false;
}

void Grid::addBombAtPlace(BombState &bomb)
{
    Point position = bomb.getPosition();
	unsigned int index = getVectorIndex(position);
    m_itemMatrix[index] = ItemBomb;
	m_idMatrix[index] = bomb.getBombId();
    bomb.setPosition(position.getGridPosition());
}

void Grid::addWallAtPlace(WallState &wall)
{
    Point position = wall.getPosition();
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemWall;
	m_idMatrix[index] = wall.getId();
}

void Grid::removeBomb(BombState &bomb)
{
	Point position = bomb.getPosition();
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;
}

void Grid::removeWall(WallState &wall)
{
	Point position = wall.getPosition();
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;
 }

void Grid::updatePlayer(const PlayerState &player)
{
    Point position = player.getPosition();
    unsigned int index = getVectorIndex(position);
    m_itemMatrix[index] = ItemPlayer;
    //m_idMatrix[index] = player.getPlayerId;
}

vector<unsigned int> Grid::getWallsInRange(const BombState &bomb) const
{
    vector<unsigned int> wallsinrange;
    Point position = bomb.getPosition();
    int x = static_cast<unsigned int>(position.getX());
    int y = static_cast<unsigned int>(position.getY());
    int range =bomb.getDestructionRange();
    bool xPlusDirectionIsWall=false;
    bool xMinusDirectionIsWall=false;
    bool yPlusDirectionIsWall=false;
    bool yMinusDirectionIsWall=false;
    for( int i=1 ; i<=range ; ++i)
    {
        if((x+i)<static_cast<int>(m_gridRows))
        {
            if (m_itemMatrix[getVectorIndex(x+i,y)] == ItemWall && xPlusDirectionIsWall==false)
            {
                wallsinrange.push_back(m_idMatrix[getVectorIndex(x+i,y)]);
                xPlusDirectionIsWall=true;
            }
        }
        if((x-i)>=0)
        {
            if (m_itemMatrix[getVectorIndex(x-i,y)] == ItemWall && xMinusDirectionIsWall==false)
            {
               wallsinrange.push_back(m_idMatrix[getVectorIndex(x-i,y)]);
               xMinusDirectionIsWall=true;
            }
        }
        if((y+i)<static_cast<int>(m_gridColumns))
        {
            if (m_itemMatrix[getVectorIndex(x,y+i)] == ItemWall && yPlusDirectionIsWall==false)
            {
                wallsinrange.push_back(m_idMatrix[getVectorIndex(x,y+i)]);
                yPlusDirectionIsWall=true;
            }
        }
        if((y-i)>=0)
        {
            if (m_itemMatrix[getVectorIndex(x,y-i)] == ItemWall && yMinusDirectionIsWall==false)
            {
                wallsinrange.push_back(m_idMatrix[getVectorIndex(x,y-i)]);
                yMinusDirectionIsWall=true;
            }
        }
    }
    return wallsinrange;
}

unsigned int Grid::getVectorIndex(const Point &position) const
{
    assert(position.getX() >= 0);
    assert(position.getY() >= 0);
    assert(position.getX() < m_gridRows);
    assert(position.getY() < m_gridColumns);
	unsigned int x = static_cast<unsigned int>(position.getX());
	unsigned int y = static_cast<unsigned int>(position.getY());
    unsigned int index = m_gridColumns*y+x;
	return index;
}

unsigned int Grid::getVectorIndex(unsigned int x,unsigned int y) const
{
    assert(x > 0);
    assert(y > 0);
    assert(x < m_gridRows);
    assert(y < m_gridColumns);
    unsigned int index = m_gridColumns*y+x;
    return index;
}
