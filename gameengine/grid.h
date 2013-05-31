#ifndef GAMEENGINE_GRID_H
#define GAMEENGINE_GRID_H

#include <vector>
#include "common/point.h"
#include "common/bombstate.h"
#include "common/wallstate.h"
#include "common/playerstate.h"
#include "common/gridpoint.h"
#include "common/powerupstate.h"

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
        ItemPowerUp,
		ItemFree
	};

public:
    Grid(unsigned int rows,unsigned int cols);

	bool isPlaceEmpty(const Common::Point &position) const;
    bool isPlaceEmpty(const Common::GridPoint &position) const;
	void addBombAtPlace(Common::BombState &bomb);
	void addWallAtPlace(Common::WallState &wall);
	void removeBomb(Common::BombState &bomb);
	void removeWall(Common::WallState &wall);
	void updatePlayer(const Common::PlayerState &player);
    void removePowerUp(Common::PowerUpState &powerUp);
    void addPowerUpAtPlace(Common::PowerUpState &powerUp);
	std::vector<unsigned int> getWallsInRange(const Common::BombState &bomb) const;
    //std::vector<Common::GridPoint> getPlayerFields(const Common::PlayerState &player) const;

private:
    unsigned int getVectorIndex(const Common::GridPoint &position) const;
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

