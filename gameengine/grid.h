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
			ItemSolidWall,
			ItemLooseWall,
			ItemBomb,
			ItemPlayer,
			ItemPowerUp,
			ItemFree
		};

	public:
		Grid(unsigned int rows,unsigned int cols);

		bool isPlaceEmpty(const Common::Point &position) const;
		bool isPlaceEmpty(const Common::GridPoint &position) const;
		bool isPlaceCoveredByWall(const Common::GridPoint &position) const;
		unsigned getId(const Common::GridPoint &position) const;
		void addBombAtPlace(Common::BombState &bomb);
		void addWallAtPlace(const Common::WallState &wall);
		void removeBomb(const Common::BombState &bomb);
		void removeWall(const Common::WallState &wall);
		void updatePlayer(const Common::PlayerState &player);
		void removePlayer(const Common::PlayerState &player);
		void removePowerUp(const Common::PowerUpState &powerUp);
		void addPowerUpAtPlace(Common::PowerUpState &powerUp);
		std::vector<unsigned int> getLooseWallsInRange(const Common::BombState &bomb) const;
		std::vector<unsigned int> getPlayersInRange(const Common::BombState &bomb) const;
		std::vector<unsigned int> getBombsInRange(const Common::BombState &bomb) const;
		std::vector<unsigned int> getPowerUpsInRange(const Common::BombState &bomb) const;
		std::vector<Common::GridPoint> getPlayerFields(const Common::PlayerState &player) const;
		std::vector<unsigned int> getPlayersInRange(const Common::BombState &bomb, std::vector<const Common::PlayerState*> allPlayers) const;
		unsigned int getBombMaximumRangeLeft(const Common::GridPoint &position) const;
		unsigned int getBombMaximumRangeUp(const Common::GridPoint &position) const;
		unsigned int getBombMaximumRangeRight(const Common::GridPoint &position) const;
		unsigned int getBombMaximumRangeDown(const Common::GridPoint &position) const;
		unsigned int getDistanceToNextWallLeft(const Common::GridPoint &position) const;
		unsigned int getDistanceToNextWallRight(const Common::GridPoint &position) const;
		unsigned int getDistanceToNextWallUp(const Common::GridPoint &position) const;
		unsigned int getDistanceToNextWallDown(const Common::GridPoint &position) const;

	private:
		unsigned int getVectorIndex(const Common::GridPoint &position) const;
		unsigned int getVectorIndex(unsigned int x, unsigned int y) const;
		std::vector<unsigned int> getItemsInRange(const Common::BombState &bomb, Grid::Item item) const;

	private:
		unsigned int m_gridRows;
		unsigned int m_gridColumns;
		unsigned int m_numberOfItems;
		std::vector<Item> m_itemMatrix;
		std::vector<unsigned int> m_idMatrix;
	};
}

#endif

