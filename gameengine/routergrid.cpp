#include "gameengine/routergrid.h"
#include "gameengine/grid.h"

using namespace GameEngine;
using namespace boost;
using namespace Common;

RouterGrid::RouterGrid(Grid &grid, const GameState &gameState) :
	GridObserver(grid),
	m_grid(grid),
	m_gameState(gameState),
	m_width(grid.getColumns()),
	m_height(grid.getRows()),
	m_fields(extents[m_height][m_width])
{
	for (unsigned int x = 0; x < m_width; ++x)
		for (unsigned int y = 0; y < m_height; ++y)
			updateFieldInternal(GridPoint(x, y));
}

void RouterGrid::fieldHasChanged(const GridPoint &position)
{
	updateFieldInternal(position);
	updateDangerousFor(position);
}

unsigned int RouterGrid::getWidth() const
{
	return m_width;
}

unsigned int RouterGrid::getHeight() const
{
	return m_height;
}

const RouterGridField &RouterGrid::getField(const GridPoint &position) const
{
	assert(position.getX() < m_width);
	assert(position.getY() < m_height);

	return m_fields[position.getY()][position.getX()];
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

	m_fields[row][column].setPlayer(player);
}

void RouterGrid::updateDangerousFor(const GridPoint &/*position*/)
{
}
