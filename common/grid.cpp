#include "common/grid.h"
#include "common/gridobserver.h"
#include "common/bombstate.h"
#include "common/wallstate.h"
#include "common/playerstate.h"
#include "common/powerupstate.h"
#include <assert.h>
#include <math.h>
#include <set>
#include <algorithm>

using namespace Common;
using namespace std;

Grid::Grid(unsigned int rows, unsigned int cols) :
	m_gridRows(rows),
	m_gridColumns(cols),
	m_numberOfItems(m_gridColumns*m_gridRows),
	m_itemMatrix(m_numberOfItems, ItemFree),
	m_idMatrix(m_numberOfItems, 0),
	m_dangerousMatrix(m_numberOfItems, 0)
{ }

Grid::~Grid()
{
	assert(m_observers.size() == 0);
}

bool Grid::isPlaceEmpty(const GridPoint &position) const
{
	unsigned int index = getVectorIndex(position);
	if(m_itemMatrix[index] == ItemFree)
		return true;
	else
		return false;
}

bool Grid::isPlaceCoveredByWall(const GridPoint &position) const
{
	unsigned int index = getVectorIndex(position);
	return m_itemMatrix[index] == ItemSolidWall || m_itemMatrix[index] == ItemLooseWall;
}

bool Grid::isPlaceCoveredByLooseWall(const GridPoint &position) const
{
	unsigned int index = getVectorIndex(position);
	return m_itemMatrix[index] == ItemLooseWall;
}

bool Grid::isPlaceCoveredBySolidWall(const GridPoint &position) const
{
	unsigned int index = getVectorIndex(position);
	return m_itemMatrix[index] == ItemSolidWall;
}

bool Grid::isPlaceCoveredByBomb(const GridPoint &position) const
{
	unsigned int index = getVectorIndex(position);
	return m_itemMatrix[index] == ItemBomb;
}

bool Grid::isPlaceDangerous(const GridPoint &position) const
{
	unsigned int index = getVectorIndex(position);
	return m_dangerousMatrix[index] > 0;
}

unsigned Grid::getId(const GridPoint &position) const
{
	assert(!isPlaceEmpty(position));
	return m_idMatrix[getVectorIndex(position)];
}

void Grid::addBombAtPlace(const BombState &bomb)
{
	GridPoint position(bomb.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemBomb;
	m_idMatrix[index] = bomb.getID();
	increaseOwnPositionDangerousCounter(bomb);
	increaseHorizontalDangerousRange(bomb);
	increaseVerticalDangerousRange(bomb);
	m_addedBombs.insert(pair<unsigned int, const BombState*>(bomb.getID(), &bomb));
	notifyObservers(position);
}

void Grid::addWallAtPlace(const WallState &wall)
{
	GridPoint position(wall.getPosition());
	unsigned int index = getVectorIndex(position);

	if (WallState::WallTypeSolid == wall.getWallType())
		m_itemMatrix[index] = ItemSolidWall;
	else
		m_itemMatrix[index] = ItemLooseWall;

	m_idMatrix[index] = wall.getId();
	notifyObservers(position);
}

void Grid::addPowerUpAtPlace(PowerUpState &powerUp)
{
	GridPoint position(powerUp.getPosition());
	vector<const BombState*> bombsOnHorizontalLine = getBombsOnHorizontalLine(position);
	vector<const BombState*> bombsOnVerticalLine = getBombsOnVerticalLine(position);

	for (vector<const BombState*>::const_iterator i = bombsOnHorizontalLine.begin(); i != bombsOnHorizontalLine.end(); ++i)
		decreaseHorizontalDangerousRange(**i);
	for (vector<const BombState*>::const_iterator i = bombsOnVerticalLine.begin(); i != bombsOnVerticalLine.end(); ++i)
		decreaseVerticalDangerousRange(**i);

	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemPowerUp;

	for (vector<const BombState*>::const_iterator i = bombsOnHorizontalLine.begin(); i != bombsOnHorizontalLine.end(); ++i)
		increaseHorizontalDangerousRange(**i);
	for (vector<const BombState*>::const_iterator i = bombsOnVerticalLine.begin(); i != bombsOnVerticalLine.end(); ++i)
		increaseVerticalDangerousRange(**i);

	m_idMatrix[index] = powerUp.getId();
}

void Grid::removePowerUp(const PowerUpState &powerUp)
{
	GridPoint position(powerUp.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;
}

void Grid::removeBomb(const BombState &bomb)
{
	GridPoint position(bomb.getPosition());
	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;
	decreaseOwnPositionDangerousCounter(bomb);
	decreaseHorizontalDangerousRange(bomb);
	decreaseVerticalDangerousRange(bomb);
	map<unsigned int, const BombState*>::iterator addedBomb = m_addedBombs.find(bomb.getID());
	m_addedBombs.erase(addedBomb);
	notifyObservers(position);
}

void Grid::removeWall(const WallState &wall)
{
	GridPoint position(wall.getPosition());
	vector<const BombState*> bombsOnHorizontalLine = getBombsOnHorizontalLine(position);
	vector<const BombState*> bombsOnVerticalLine = getBombsOnVerticalLine(position);

	for (vector<const BombState*>::const_iterator i = bombsOnHorizontalLine.begin(); i != bombsOnHorizontalLine.end(); ++i)
		decreaseHorizontalDangerousRange(**i);
	for (vector<const BombState*>::const_iterator i = bombsOnVerticalLine.begin(); i != bombsOnVerticalLine.end(); ++i)
		decreaseVerticalDangerousRange(**i);

	unsigned int index = getVectorIndex(position);
	m_itemMatrix[index] = ItemFree;
	m_idMatrix[index] = 0;

	for (vector<const BombState*>::const_iterator i = bombsOnHorizontalLine.begin(); i != bombsOnHorizontalLine.end(); ++i)
		increaseHorizontalDangerousRange(**i);
	for (vector<const BombState*>::const_iterator i = bombsOnVerticalLine.begin(); i != bombsOnVerticalLine.end(); ++i)
		increaseVerticalDangerousRange(**i);

	notifyObservers(position);
}

vector<unsigned int> Grid::getItemsInRange(const BombState &bomb, Grid::Item item) const
{
	vector<unsigned int> itemsInRange;
	GridPoint position(bomb.getPosition());
	int x = position.getX();
	int y = position.getY();
	int range = bomb.getDestructionRange();
	bool isWallRightReached = false;
	bool isWallLeftReached = false;
	bool isWallUpReached = false;
	bool isWallDownReached = false;

	for(int i = 1 ; i <= range ; ++i)
	{
		if((x + i) < static_cast<int>(m_gridColumns))
		{
			if (m_itemMatrix[getVectorIndex(x + i, y)] == item && !isWallRightReached)
				itemsInRange.push_back(m_idMatrix[getVectorIndex(x + i, y)]);

			if(isPlaceCoveredByWall(GridPoint(x + i, y)))
				isWallRightReached = true;
		}

		if((x - i) >= 0)
		{
			if (m_itemMatrix[getVectorIndex(x - i, y)] == item && !isWallLeftReached)
				itemsInRange.push_back(m_idMatrix[getVectorIndex(x - i, y)]);

			if(isPlaceCoveredByWall(GridPoint(x - i, y)))
				isWallLeftReached = true;
		}

		if((y + i) < static_cast<int>(m_gridRows))
		{
			if (m_itemMatrix[getVectorIndex(x, y + i)] == item && !isWallUpReached)
				itemsInRange.push_back(m_idMatrix[getVectorIndex(x, y + i)]);

			if(isPlaceCoveredByWall(GridPoint(x, y + i)))
				isWallUpReached = true;
		}

		if((y - i) >= 0)
		{
			if (m_itemMatrix[getVectorIndex(x, y - i)] == item && !isWallDownReached)
				itemsInRange.push_back(m_idMatrix[getVectorIndex(x, y - i)]);

			if(isPlaceCoveredByWall(GridPoint(x, y - i)))
				isWallDownReached = true;
		}
	}

	return itemsInRange;
}

void Grid::notifyObservers(const GridPoint &position)
{
	for (vector<GridObserver*>::const_iterator i = m_observers.begin(); i != m_observers.end(); ++i)
		(*i)->fieldHasChanged(position);
}

void Grid::increaseHorizontalDangerousRange(const BombState &bomb)
{
	GridPoint bombPosition = bomb.getPosition();
	unsigned int rangeLeft = getBombMaximumRangeLeft(bombPosition);
	unsigned int rangeRight = getBombMaximumRangeRight(bombPosition);

	for (unsigned int x = bombPosition.getX() - rangeLeft; x <= bombPosition.getX() + rangeRight; ++x)
	{
		GridPoint position(x, bombPosition.getY());
		unsigned int index = getVectorIndex(position);
		++m_dangerousMatrix[index];
	}
}

void Grid::increaseVerticalDangerousRange(const BombState &bomb)
{
	GridPoint bombPosition = bomb.getPosition();
	unsigned int rangeDown = getBombMaximumRangeDown(bombPosition);
	unsigned int rangeUp = getBombMaximumRangeUp(bombPosition);

	for (unsigned int y = bombPosition.getY() - rangeDown; y <= bombPosition.getY() + rangeUp; ++y)
	{
		GridPoint position(bombPosition.getX(), y);
		unsigned int index = getVectorIndex(position);
		++m_dangerousMatrix[index];
	}
}

void Grid::increaseOwnPositionDangerousCounter(const BombState &bomb)
{
	GridPoint bombPosition = bomb.getPosition();
	unsigned int index = getVectorIndex(bombPosition);
	++m_dangerousMatrix[index];
}

void Grid::decreaseHorizontalDangerousRange(const BombState &bomb)
{
	GridPoint bombPosition = bomb.getPosition();
	unsigned int rangeLeft = getBombMaximumRangeLeft(bombPosition);
	unsigned int rangeRight = getBombMaximumRangeRight(bombPosition);

	for (unsigned int x = bombPosition.getX() - rangeLeft; x <= bombPosition.getX() + rangeRight; ++x)
	{
		GridPoint position(x, bombPosition.getY());
		unsigned int index = getVectorIndex(position);
		assert(m_dangerousMatrix[index] > 0);
		--m_dangerousMatrix[index];
	}
}

void Grid::decreaseVerticalDangerousRange(const BombState &bomb)
{
	GridPoint bombPosition = bomb.getPosition();
	unsigned int rangeDown = getBombMaximumRangeDown(bombPosition);
	unsigned int rangeUp = getBombMaximumRangeUp(bombPosition);

	for (unsigned int y = bombPosition.getY() - rangeDown; y <= bombPosition.getY() + rangeUp; ++y)
	{
		GridPoint position(bombPosition.getX(), y);
		unsigned int index = getVectorIndex(position);
		assert(m_dangerousMatrix[index] > 0);
		--m_dangerousMatrix[index];
	}
}

void Grid::decreaseOwnPositionDangerousCounter(const BombState &bomb)
{
	GridPoint bombPosition = bomb.getPosition();
	unsigned int index = getVectorIndex(bombPosition);
	assert(m_dangerousMatrix[index] > 0);
	--m_dangerousMatrix[index];
}

vector<const BombState*> Grid::getBombsOnHorizontalLine(const GridPoint &position) const
{
	vector<const BombState*> result;

	for (unsigned int x = 0; x < m_gridColumns; ++x)
	{
		GridPoint newPosition(x, position.getY());

		if (isPlaceCoveredByBomb(newPosition))
		{
			unsigned int id = getId(newPosition);
			result.push_back(m_addedBombs.at(id));
		}
	}

	return result;
}

vector<const BombState*> Grid::getBombsOnVerticalLine(const GridPoint &position) const
{
	vector<const BombState*> result;

	for (unsigned int y = 0; y < m_gridRows; ++y)
	{
		GridPoint newPosition(position.getX(), y);

		if (isPlaceCoveredByBomb(newPosition))
		{
			unsigned int id = getId(newPosition);
			result.push_back(m_addedBombs.at(id));
		}
	}

	return result;
}

vector<unsigned int> Grid::getLooseWallsInRange(const BombState &bomb) const
{
	return getItemsInRange(bomb, ItemLooseWall);
}

vector<unsigned int> Grid::getBombsInRange(const BombState &bomb) const
{
	return getItemsInRange(bomb, ItemBomb);
}

vector<unsigned int> Grid::getPowerUpsInRange(const BombState &bomb) const
{
	return getItemsInRange(bomb, ItemPowerUp);
}

unsigned int Grid::getVectorIndex(const GridPoint &position) const
{
	assert(position.getX() < m_gridColumns);
	assert(position.getY() < m_gridRows);
	unsigned int x = position.getX();
	unsigned int y = position.getY();
	unsigned int index = m_gridColumns*y+x;
	return index;
}

unsigned int Grid::getVectorIndex(unsigned int x,unsigned int y) const
{
	assert(x< m_gridColumns);
	assert(y< m_gridRows);
	unsigned int index = m_gridColumns*y+x;
	return index;
}

vector<GridPoint> Grid::getPlayerFields(const Common::PlayerState &player)
{
	Point position = player.getPosition();
	vector<GridPoint> fields = GridPoint::getCoveredGridPoints(position);
	return fields;
}

bool xIsSmaller(const GridPoint &rhs, const GridPoint &lhs)
{
	return rhs.getX() < lhs.getX();
}

bool yIsSmaller(const GridPoint &rhs, const GridPoint &lhs)
{
	return rhs.getY() < lhs.getY();
}

GridPoint Grid::getTargetPoint(const PlayerState &player)
{
	vector<GridPoint> fields = getPlayerFields(player);

	if (fields.size() == 1)
		return fields[0];

	GridPoint result;

	if (player.getDirection() == PlayerState::PlayerDirectionLeft || player.getDirection() == PlayerState::PlayerDirectionRight)
	{
		sort(fields.begin(), fields.end(), &xIsSmaller);

		if (player.getDirection() == PlayerState::PlayerDirectionLeft)
			result = fields[0];
		else
			result = fields[1];
	}
	else
	{
		sort(fields.begin(), fields.end(), &yIsSmaller);

		if (player.getDirection() == PlayerState::PlayerDirectionDown)
			result = fields[0];
		else
			result = fields[1];
	}

	return result;
}

std::vector<unsigned int> Grid::getPlayersInRange(const BombState &bomb, vector<const PlayerState*> allPlayers) const
{
	typedef pair<GridPoint, unsigned int> PositionAndID;
	vector<PositionAndID> playerPositionsAndID;
	GridPoint bombPosition(bomb.getPosition());
	set<unsigned int> playersInRange;

	for (vector<const PlayerState*>::const_iterator i = allPlayers.begin(); i != allPlayers.end(); ++i)
	{
		const PlayerState &player = **i;
		vector<GridPoint> positions = getPlayerFields(player);

		for (vector<GridPoint>::const_iterator j = positions.begin(); j != positions.end(); ++j)
			playerPositionsAndID.push_back(PositionAndID(*j, player.getId()));
	}

	unsigned int maximumDestructionRange = bomb.getDestructionRange();
	unsigned int destructionRangeLeft = min(getBombMaximumRangeLeft(bombPosition), maximumDestructionRange);
	unsigned int destructionRangeUp = min(getBombMaximumRangeUp(bombPosition), maximumDestructionRange);
	unsigned int destructionRangeRight = min(getBombMaximumRangeRight(bombPosition), maximumDestructionRange);
	unsigned int destructionRangeDown = min(getBombMaximumRangeDown(bombPosition), maximumDestructionRange);

	for (vector<PositionAndID>::const_iterator i = playerPositionsAndID.begin(); i != playerPositionsAndID.end(); ++i)
	{
		GridPoint playerPosition = i->first;

		if (	playerPosition.getY() == bombPosition.getY() &&
				bombPosition.getX() - destructionRangeLeft <= playerPosition.getX() &&
				bombPosition.getX() + destructionRangeRight >= playerPosition.getX())
		{
			unsigned int playerID = i->second;
			playersInRange.insert(playerID);
		}
	}

	for (vector<PositionAndID>::const_iterator i = playerPositionsAndID.begin(); i != playerPositionsAndID.end(); ++i)
	{
		GridPoint playerPosition = i->first;

		if (	playerPosition.getX() == bombPosition.getX() &&
				bombPosition.getY() - destructionRangeDown <= playerPosition.getY() &&
				bombPosition.getY() + destructionRangeUp >= playerPosition.getY())
		{
			unsigned int playerID = i->second;
			playersInRange.insert(playerID);
		}
	}

	vector<unsigned int> result;
	result.reserve(playersInRange.size());
	for (set<unsigned int>::const_iterator i = playersInRange.begin(); i != playersInRange.end(); ++i)
		result.push_back(*i);
	return result;
}

unsigned int Grid::getDistanceToNextWallLeft(const GridPoint &position) const
{
	unsigned int distance;

	for (distance = 1; position.getX() - distance < m_gridColumns; ++distance)
		if (isPlaceCoveredByWall(position - GridPoint(distance, 0)))
			return distance - 1;

	return distance - 1;
}

unsigned int Grid::getDistanceToNextWallRight(const GridPoint &position) const
{
	unsigned int distance;

	for (distance = 1; position.getX() + distance < m_gridColumns; ++distance)
		if (isPlaceCoveredByWall(position + GridPoint(distance, 0)))
			return distance - 1;

	return distance - 1;
}

unsigned int Grid::getDistanceToNextWallUp(const GridPoint &position) const
{
	unsigned int distance;

	for (distance = 1; position.getY() + distance < m_gridRows; ++distance)
		if (isPlaceCoveredByWall(position + GridPoint(0, distance)))
			return distance - 1;

	return distance - 1;
}

unsigned int Grid::getDistanceToNextWallDown(const GridPoint &position) const
{
	unsigned int distance;

	for (distance = 1; position.getY() - distance < m_gridRows; ++distance)
		if (isPlaceCoveredByWall(position - GridPoint(0, distance)))
			return distance - 1;

	return distance - 1;
}

void Grid::unregisterObserver(GridObserver &observer)
{
	assert(count(m_observers.begin(), m_observers.end(), &observer) == 1);
	vector<GridObserver*>::iterator newEnd = remove(m_observers.begin(), m_observers.end(), &observer);
	m_observers.erase(newEnd, m_observers.end());
}

void Grid::registerObserver(GridObserver &observer)
{
	assert(count(m_observers.begin(), m_observers.end(), &observer) == 0);
	m_observers.push_back(&observer);
}

size_t Grid::getObserverCount() const
{
	return m_observers.size();
}

unsigned int Grid::getRows() const
{
	return m_gridRows;
}

unsigned int Grid::getColumns() const
{
	return m_gridColumns;
}

unsigned int Grid::getBombMaximumRangeLeft(const GridPoint &position) const
{
	unsigned int distanceToNextWall = getDistanceToNextWallLeft(position);

	if (position.getX() - distanceToNextWall - 1 < m_gridColumns)
	{
		GridPoint endPosition(position - GridPoint(distanceToNextWall + 1, 0));
		unsigned int vectorIndex = getVectorIndex(endPosition);
		Item itemType = m_itemMatrix[vectorIndex];

		if (itemType == ItemLooseWall)
			return distanceToNextWall + 1;
	}

	return distanceToNextWall;
}

unsigned int Grid::getBombMaximumRangeUp(const GridPoint &position) const
{
	unsigned int distanceToNextWall = getDistanceToNextWallUp(position);

	if (position.getY() + distanceToNextWall + 1 < m_gridRows)
	{
		GridPoint endPosition(position + GridPoint(0, distanceToNextWall + 1));
		unsigned int vectorIndex = getVectorIndex(endPosition);
		Item itemType = m_itemMatrix[vectorIndex];

		if (itemType == ItemLooseWall)
			return distanceToNextWall + 1;
	}

	return distanceToNextWall;
}

unsigned int Grid::getBombMaximumRangeRight(const GridPoint &position) const
{
	unsigned int distanceToNextWall = getDistanceToNextWallRight(position);

	if (position.getX() + distanceToNextWall + 1 < m_gridColumns)
	{
		GridPoint endPosition(position + GridPoint(distanceToNextWall + 1, 0));
		unsigned int vectorIndex = getVectorIndex(endPosition);
		Item itemType = m_itemMatrix[vectorIndex];

		if (itemType == ItemLooseWall)
			return distanceToNextWall + 1;
	}

	return distanceToNextWall;
}

unsigned int Grid::getBombMaximumRangeDown(const GridPoint &position) const
{
	unsigned int distanceToNextWall = getDistanceToNextWallDown(position);

	if (position.getY() - distanceToNextWall - 1 < m_gridRows)
	{
		GridPoint endPosition(position - GridPoint(0, distanceToNextWall + 1));
		unsigned int vectorIndex = getVectorIndex(endPosition);
		Item itemType = m_itemMatrix[vectorIndex];

		if (itemType == ItemLooseWall)
			return distanceToNextWall + 1;
	}

	return distanceToNextWall;
}
