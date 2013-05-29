#include "grid.h"
#include<assert.h>

using namespace Common;
using namespace GameEngine;
using namespace std;

Grid::Grid(double width,double height) :
	m_gridRows(static_cast<unsigned int>(height)),
	m_gridColumns(static_cast<unsigned int>(width)),
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

Point Grid::addBombAtPlace(const BombState &bomb)
{
    Point position = bomb.getPosition();
	unsigned int index = getVectorIndex(position);
    m_itemMatrix[index] = ItemBomb;
	m_idMatrix[index] = bomb.getBombId();
    return position.getGridPosition();
}

Point Grid::addWallAtPlace(const WallState &wall)
{
	Point position = wall.getPosition();
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemWall;
	m_idMatrix[index] = wall.getWallId();
    return position.getGridPosition();
}

void Grid::removeBomb(const BombState &bomb)
{
	Point position = bomb.getPosition();
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;
}

void Grid::removeWall(const WallState &wall)
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
    bool xplusdirectioniswall=false;
    bool xminusdirectioniswall=false;
    bool yplusdirectioniswall=false;
    bool yminusdirectioniswall=false;
    for( int i=1 ; i<=range ; ++i)
    {
        if((x+i)<static_cast<int>(m_gridRows))
        {
            if (m_itemMatrix[getVectorIndex(x+i,y)] == ItemWall && xplusdirectioniswall==false)
            {
                wallsinrange.push_back(m_idMatrix[getVectorIndex(x+i,y)]);
                xplusdirectioniswall=true;
            }
        }
        if((x-i)>=0)
        {
            if (m_itemMatrix[getVectorIndex(x-i,y)] == ItemWall && xminusdirectioniswall==false)
            {
               wallsinrange.push_back(m_idMatrix[getVectorIndex(x-i,y)]);
               xminusdirectioniswall=true;
            }
        }
        if((y+i)<static_cast<int>(m_gridColumns))
        {
            if (m_itemMatrix[getVectorIndex(x,y+i)] == ItemWall && yplusdirectioniswall==false)
            {
                wallsinrange.push_back(m_idMatrix[getVectorIndex(x,y+i)]);
                yplusdirectioniswall=true;
            }
        }
        if((y-i)>=0)
        {
            if (m_itemMatrix[getVectorIndex(x,y-i)] == ItemWall && yminusdirectioniswall==false)
            {
                wallsinrange.push_back(m_idMatrix[getVectorIndex(x,y-i)]);
                yminusdirectioniswall=true;
            }
        }
    }
    return wallsinrange;
}

unsigned int Grid::getVectorIndex(const Point &position) const
{
    assert(position.getX() > 0);
    assert(position.getY() > 0);
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
