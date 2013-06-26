#include "gameengine/routergrid.h"
#include "common/grid.h"
#include "common/gamestate.h"
#include <algorithm>

using namespace GameEngine;
using namespace Common;
using namespace std;
using namespace boost;

RouterGrid::RouterGrid(Grid &grid, const GameState &gameState, unsigned int playerID) :
	GridObserver(grid),
	m_grid(grid),
	m_gameState(gameState),
	m_width(grid.getColumns()),
	m_height(grid.getRows()),
	m_fields(extents[m_height][m_width]),
	m_ownPlayerId(playerID)
{
	for (unsigned int x = 0; x < m_width; ++x)
		for (unsigned int y = 0; y < m_height; ++y)
			updateFieldInternal(GridPoint(x, y));

	updateDangerousFlags();
}

void RouterGrid::fieldHasChanged(const GridPoint &position)
{
	updateFieldInternal(position);
	removeDangerousFlags();
	updateDangerousFlags();
}

unsigned int RouterGrid::getWidth() const
{
	return m_width;
}

unsigned int RouterGrid::getHeight() const
{
	return m_height;
}

const RouterGridField& RouterGrid::getField(const GridPoint &position) const
{
	assert(position.getX() < m_width);
	assert(position.getY() < m_height);

	return m_fields[position.getY()][position.getX()];
}

void RouterGrid::updatePlayerFlags()
{
	removePlayerFlags();
	vector<GridPoint> playerFields = getAllPlayerFields();

	for (vector<GridPoint>::const_iterator i = playerFields.begin(); i != playerFields.end(); ++i)
	{
		RouterGridField &field = getFieldInternal(*i);
		field.setPlayer(true);
	}
}

RouterGridField& RouterGrid::getFieldInternal(const GridPoint &position)
{
	assert(position.getX() < m_width);
	assert(position.getY() < m_height);

	return m_fields[position.getY()][position.getX()];
}

void RouterGrid::markFieldsAsDangerousIfCoveredByBomb(const GridPoint &position)
{
	unsigned int row = position.getY();
	unsigned int column = position.getX();

	if (!m_fields[row][column].isBomb())
		return;

	assert(m_grid.isPlaceCoveredByBomb(position));
	unsigned int bombID = m_grid.getId(position);
	const BombState &bomb = m_gameState.getBombById(bombID);
	unsigned int maximumRangeLeft = m_grid.getBombMaximumRangeLeft(position);
	unsigned int maximumRangeUp = m_grid.getBombMaximumRangeUp(position);
	unsigned int maximumRangeRight = m_grid.getBombMaximumRangeRight(position);
	unsigned int maximumRangeDown = m_grid.getBombMaximumRangeDown(position);
	unsigned int rangeLeft = min(maximumRangeLeft, bomb.getDestructionRange());
	unsigned int rangeUp = min(maximumRangeUp, bomb.getDestructionRange());
	unsigned int rangeRight = min(maximumRangeRight, bomb.getDestructionRange());
	unsigned int rangeDown = min(maximumRangeDown, bomb.getDestructionRange());

	for (unsigned int i = 0; i <= rangeLeft; ++i)
		m_fields[row][column - i].setDangerous(true);
	for (unsigned int i = 0; i <= rangeRight; ++i)
		m_fields[row][column + i].setDangerous(true);
	for (unsigned int i = 0; i <= rangeDown; ++i)
		m_fields[row - i][column].setDangerous(true);
	for (unsigned int i = 0; i <= rangeUp; ++i)
		m_fields[row + i][column].setDangerous(true);
}

void RouterGrid::updateFieldInternal(const GridPoint &position)
{
	unsigned int row = position.getY();
	unsigned int column = position.getX();

	assert(column < m_width);
	assert(row < m_height);

	bool player = m_fields[row][column].isPlayer();
	m_fields[row][column].clear();

	if (m_grid.isPlaceCoveredByBomb(position))
		m_fields[row][column].setBomb(true);
	else if (m_grid.isPlaceCoveredByLooseWall(position))
		m_fields[row][column].setLooseWall(true);
	else if (m_grid.isPlaceCoveredBySolidWall(position))
		m_fields[row][column].setSolidWall(true);
	else if (m_grid.isPlaceCoveredByPowerUp(position))
		m_fields[row][column].setPowerUp(true);

	m_fields[row][column].setPlayer(player);
}

void RouterGrid::removeDangerousFlags()
{
	for (unsigned int x = 0; x < m_width; ++x)
		for (unsigned int y = 0; y < m_height; ++y)
			if (!m_fields[y][x].isBomb())
				m_fields[y][x].setDangerous(false);
}

void RouterGrid::updateDangerousFlags()
{
	for (unsigned int x = 0; x < m_width; ++x)
		for (unsigned int y = 0; y < m_height; ++y)
			markFieldsAsDangerousIfCoveredByBomb(GridPoint(x, y));
}

void RouterGrid::removePlayerFlags()
{
	for (unsigned int x = 0; x < m_width; ++x)
		for (unsigned int y = 0; y < m_height; ++y)
			m_fields[y][x].setPlayer(false);
}

vector<GridPoint> RouterGrid::getAllPlayerFields() const
{
	vector<GridPoint> result;
	vector<const PlayerState*> players = m_gameState.getAllPlayers();

	for (vector<const PlayerState*>::const_iterator i = players.begin(); i != players.end(); ++i)
	{
		if ((*i)->getId() == m_ownPlayerId)
			continue;

		vector<GridPoint> resultPart = m_grid.getPlayerFields(**i);
		result.insert(result.end(), resultPart.begin(), resultPart.end());
	}

	return result;
}
