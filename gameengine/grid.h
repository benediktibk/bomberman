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
    Common::Point addBombAtPlace(const Common::BombState &bomb);
    Common::Point addWallAtPlace(const Common::WallState &wall);
	void removeBomb(const Common::BombState &bomb);
	void removeWall(const Common::WallState &wall);
	void updatePlayer(const Common::PlayerState &player);
    std::vector<unsigned int> getWallsInRange(const Common::BombState &bomb) const;

private:
	unsigned int getVectorIndex(const Common::Point &position) const;
    unsigned int getVectorIndex(unsigned int x,unsigned int y) const;
private:
	unsigned int m_gridRows;
	unsigned int m_gridColumns;
	unsigned int m_numberOfItems;
	std::vector<Item> m_itemMatrix;
	std::vector<unsigned int> m_idMatrix;
};
}

#endif

