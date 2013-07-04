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

		bool isPlaceEmpty(const GridPoint &position) const;
		bool isPlaceCoveredByWall(const GridPoint &position) const;
		bool isPlaceCoveredByLooseWall(const GridPoint &position) const;
		bool isPlaceCoveredBySolidWall(const GridPoint &position) const;
		bool isPlaceCoveredByBomb(const GridPoint &position) const;
		bool isPlaceDangerous(const GridPoint &position) const;
		bool isPlaceCoveredByPowerUp(const GridPoint &position) const;
		unsigned getId(const GridPoint &position) const;
		void addBombAtPlace(const BombState &bomb);
		void addWallAtPlace(const WallState &wall);
		void addBombForPositionCheck(const BombState &bomb);
		void removeBomb(const BombState &bomb);
		void removeWall(const WallState &wall);
		void removePowerUp(const Common::PowerUpState &powerUp);
		void removeBombForPositionCheck(const BombState &bomb);
		void addPowerUpAtPlace(Common::PowerUpState &powerUp);
		std::vector<unsigned int> getLooseWallsInRange(const BombState &bomb) const;
		std::vector<unsigned int> getBombsInRange(const BombState &bomb) const;
		std::vector<unsigned int> getPowerUpsInRange(const BombState &bomb) const;
		std::vector<unsigned int> getPlayersInRange(const BombState &bomb, std::vector<const PlayerState*> allPlayers) const;
		unsigned int getBombRangeLeft(const BombState &bomb) const;
		unsigned int getBombRangeRight(const BombState &bomb) const;
		unsigned int getBombRangeUp(const BombState &bomb) const;
		unsigned int getBombRangeDown(const BombState &bomb) const;
		unsigned int getDistanceToNextWallLeft(const GridPoint &position) const;
		unsigned int getDistanceToNextWallRight(const GridPoint &position) const;
		unsigned int getDistanceToNextWallUp(const GridPoint &position) const;
		unsigned int getDistanceToNextWallDown(const GridPoint &position) const;
		void unregisterObserver(GridObserver &observer);
		void registerObserver(GridObserver &observer);
		size_t getObserverCount() const;
		unsigned int getRows() const;
		unsigned int getColumns() const;
		std::vector<GridPoint> getAllFieldsBesideBombRange(const GridPoint &position, unsigned int range);

	public:
		static std::vector<GridPoint> getPlayerFields(const PlayerState &player);
		static GridPoint getTargetPoint(const PlayerState &player);

	private:
		unsigned int getVectorIndex(const GridPoint &position) const;
		unsigned int getVectorIndex(unsigned int x, unsigned int y) const;
		std::vector<unsigned int> getItemsInRange(const BombState &bomb, Grid::Item item) const;
		void notifyObservers(const GridPoint &position);
		void increaseHorizontalDangerousRange(const BombState &bomb);
		void increaseVerticalDangerousRange(const BombState &bomb);
		void increaseOwnPositionDangerousCounter(const BombState &bomb);
		void decreaseHorizontalDangerousRange(const BombState &bomb);
		void decreaseVerticalDangerousRange(const BombState &bomb);
		void decreaseOwnPositionDangerousCounter(const BombState &bomb);
		std::vector<const BombState*> getBombsOnHorizontalLine(const GridPoint &position) const;
		std::vector<const BombState*> getBombsOnVerticalLine(const GridPoint &position) const;
		unsigned int getBombMaximumRangeLeft(const GridPoint &position) const;
		unsigned int getBombMaximumRangeUp(const GridPoint &position) const;
		unsigned int getBombMaximumRangeRight(const GridPoint &position) const;
		unsigned int getBombMaximumRangeDown(const GridPoint &position) const;
		void removeRangesFromMatrix(const std::vector<const BombState*> &horizontal, const std::vector<const BombState*> &vertical);
		void addRangesToMatrix(const std::vector<const BombState*> &horizontal, const std::vector<const BombState*> &vertical);

	private:
		unsigned int m_rows;
		unsigned int m_columns;
		unsigned int m_numberOfItems;
		std::vector<Item> m_itemMatrix;
		std::vector<unsigned int> m_idMatrix;
		std::vector<GridObserver*> m_observers;
		std::vector<unsigned int> m_dangerousMatrix;
		std::map<unsigned int, const BombState*> m_addedBombs;
	};
}

#endif

