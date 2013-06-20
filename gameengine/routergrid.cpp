#include "gameengine/routergrid.h"
#include "gameengine/grid.h"

using namespace GameEngine;
using namespace boost;

RouterGrid::RouterGrid(Grid &grid) :
	GridObserver(grid),
	m_grid(grid),
	m_width(grid.getColumns()),
	m_height(grid.getRows()),
	m_fields(extents[m_height][m_width])
{ }

void RouterGrid::fieldHasChanged(const Common::GridPoint &position)
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

	updateDangerousFor(row, column);
}

unsigned int RouterGrid::getWidth() const
{
	return m_width;
}

unsigned int RouterGrid::getHeight() const
{
	return m_height;
}

const RouterGridField &RouterGrid::getField(const Common::GridPoint &position) const
{
	assert(position.getX() < m_width);
	assert(position.getY() < m_height);

	return m_fields[position.getY()][position.getX()];
}

void RouterGrid::updateDangerousFor(unsigned int /*row*/, unsigned int /*column*/)
{
}
