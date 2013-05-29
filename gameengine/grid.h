#ifndef GRID_H
#define GRID_H

#include <vector>
#include "common/point.h"
#include "common/bombstate.h"
#include "common/wallstate.h"
#include "common/playerstate.h"

namespace GameEngine
{
class Grid
{
private:
	enum Item
	{
		ItemWall,
		ItemBomb,
		ItemPlayer,
		ItemFree
	};

public:
	Grid(double width,double height);

	bool isPlaceEmpty(const Common::Point &position) const;
    Common::Point addBombAtPlace(Common::BombState &bomb);
    Common::Point addWallAtPlace(Common::WallState &wall);
    void removeBomb(Common::BombState &bomb);
    void removeWall(Common::WallState &wall);
	void updatePlayer(const Common::PlayerState &player);

private:
	unsigned int getVectorIndex(const Common::Point &position) const;

private:
	unsigned int m_gridRows;
	unsigned int m_gridColumns;
	unsigned int m_numberOfItems;
	std::vector<Item> m_itemMatrix;
	std::vector<unsigned int> m_idMatrix;
};
}

#endif

