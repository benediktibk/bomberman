#include "grid.h"
#include<assert.h>

using namespace Common;
using namespace GameEngine;

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
	m_idMatrix[index] = wall.getWallId();
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
