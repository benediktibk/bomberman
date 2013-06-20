#include "gameengine/routergrid.h"
#include "gameengine/grid.h"

using namespace GameEngine;

RouterGrid::RouterGrid(Grid &grid) :
	GridObserver(grid),
	m_width(grid.getColumns()),
	m_height(grid.getRows())
{ }

void RouterGrid::fieldHasChanged(const Common::GridPoint &/*position*/)
{
}

unsigned int RouterGrid::getWidth() const
{
	return m_width;
}

unsigned int RouterGrid::getHeight() const
{
	return m_height;
}
