#ifndef COMMON_GRID_H
#define COMMON_GRID_H

#include <vector>
#include <map>
#include "common/point.h"
#include "common/gridpoint.h"

namespace Common
{
	class BombState;
	class WallState;
	class PlayerState;
	class PowerUpState;
}

namespace Common
{
	class GridObserver;

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
		Grid(unsigned int rows, unsigned int cols);
		~Grid();

		bool isPlaceEmpty(const Common::GridPoint &position) const;
		bool isPlaceCoveredByWall(const Common::GridPoint &position) const;
		bool isPlaceCoveredByLooseWall(const Common::GridPoint &position) const;
		bool isPlaceCoveredBySolidWall(const Common::GridPoint &position) const;
		bool isPlaceCoveredByBomb(const Common::GridPoint &position) const;
		bool isPlaceDangerous(const Common::GridPoint &position) const;
		unsigned getId(const Common::GridPoint &position) const;
		void addBombAtPlace(const BombState &bomb);
		void addWallAtPlace(const Common::WallState &wall);
		void removeBomb(const Common::BombState &bomb);
		void removeWall(const Common::WallState &wall);
		void removePowerUp(const Common::PowerUpState &powerUp);
		void addPowerUpAtPlace(Common::PowerUpState &powerUp);
		std::vector<unsigned int> getLooseWallsInRange(const Common::BombState &bomb) const;
		std::vector<unsigned int> getBombsInRange(const Common::BombState &bomb) const;
		std::vector<unsigned int> getPowerUpsInRange(const Common::BombState &bomb) const;
		std::vector<unsigned int> getPlayersInRange(const Common::BombState &bomb, std::vector<const Common::PlayerState*> allPlayers) const;
		unsigned int getBombRangeLeft(const BombState &bomb) const;
		unsigned int getBombRangeRight(const BombState &bomb) const;
		unsigned int getBombRangeUp(const BombState &bomb) const;
		unsigned int getBombRangeDown(const BombState &bomb) const;
		unsigned int getDistanceToNextWallLeft(const Common::GridPoint &position) const;
		unsigned int getDistanceToNextWallRight(const Common::GridPoint &position) const;
		unsigned int getDistanceToNextWallUp(const Common::GridPoint &position) const;
		unsigned int getDistanceToNextWallDown(const Common::GridPoint &position) const;
		void unregisterObserver(GridObserver &observer);
		void registerObserver(GridObserver &observer);
		size_t getObserverCount() const;
		unsigned int getRows() const;
		unsigned int getColumns() const;

	public:
		static std::vector<Common::GridPoint> getPlayerFields(const Common::PlayerState &player);
		static Common::GridPoint getTargetPoint(const Common::PlayerState &player);

	private:
		unsigned int getVectorIndex(const Common::GridPoint &position) const;
		unsigned int getVectorIndex(unsigned int x, unsigned int y) const;
		std::vector<unsigned int> getItemsInRange(const Common::BombState &bomb, Grid::Item item) const;
		void notifyObservers(const Common::GridPoint &position);
		void increaseHorizontalDangerousRange(const Common::BombState &bomb);
		void increaseVerticalDangerousRange(const Common::BombState &bomb);
		void increaseOwnPositionDangerousCounter(const Common::BombState &bomb);
		void decreaseHorizontalDangerousRange(const Common::BombState &bomb);
		void decreaseVerticalDangerousRange(const Common::BombState &bomb);
		void decreaseOwnPositionDangerousCounter(const Common::BombState &bomb);
		std::vector<const BombState*> getBombsOnHorizontalLine(const GridPoint &position) const;
		std::vector<const BombState*> getBombsOnVerticalLine(const GridPoint &position) const;
		unsigned int getBombMaximumRangeLeft(const Common::GridPoint &position) const;
		unsigned int getBombMaximumRangeUp(const Common::GridPoint &position) const;
		unsigned int getBombMaximumRangeRight(const Common::GridPoint &position) const;
		unsigned int getBombMaximumRangeDown(const Common::GridPoint &position) const;

	private:
		unsigned int m_gridRows;
		unsigned int m_gridColumns;
		unsigned int m_numberOfItems;
		std::vector<Item> m_itemMatrix;
		std::vector<unsigned int> m_idMatrix;
		std::vector<GridObserver*> m_observers;
		std::vector<unsigned int> m_dangerousMatrix;
		std::map<unsigned int, const BombState*> m_addedBombs;
	};
}

#endif

