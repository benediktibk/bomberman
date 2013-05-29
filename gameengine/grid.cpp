#include "grid.h"

using namespace Common;
using namespace GameEngine;

Grid::Grid(double width,double height) :
    m_gridRows(static_cast<unsigned int>(height)),
    m_gridColumns(static_cast<unsigned int>(width)),
    m_numberOfItems(m_gridColumns*m_gridRows),
    m_itemMatrix(m_numberOfItems,ItemFree),
    m_idMatrix(m_numberOfItems,0)
{
}

bool Grid::isPlaceEmpty(const Common::Point &position) const
{
unsigned int index=getVectorIndex(position);
if(m_itemMatrix[index]==ItemFree)
    return true;
else
    return false;
}

void Grid::addBombAtPlace(const Common::BombState &bomb)
{
    Point position=bomb.getPosition();
    unsigned int index=getVectorIndex(position);
    m_itemMatrix[index]=ItemBomb;
    m_idMatrix[index]=bomb.getBombId();
}

void Grid::addWallAtPlace(const Common::WallState &wall)
{
    Point position=wall.getPosition();
    unsigned int index=getVectorIndex(position);
    m_itemMatrix[index]=ItemWall;
    m_idMatrix[index]=wall.getWallId();
}

void Grid::removeBomb(const Common::BombState &bomb)
{
    Point position=bomb.getPosition();
    unsigned int index=getVectorIndex(position);
    m_itemMatrix[index]=ItemFree;
    m_idMatrix[index]=0;
}

void Grid::removeWall(const Common::WallState &wall)
{
    Point position=wall.getPosition();
    unsigned int index=getVectorIndex(position);
    m_itemMatrix[index]=ItemFree;
    m_idMatrix[index]=0;
 }
//
//void Grid::updatePlayer(const Common::PlayerState &player)
//{
//
//}

unsigned int Grid::getVectorIndex(const Common::Point &position) const
{
    unsigned int x = static_cast<unsigned int>(position.getX());
    unsigned int y = static_cast<unsigned int>(position.getY());
    unsigned int index = ((m_gridRows-y-1)*m_gridColumns)+x;
    return index;
}
