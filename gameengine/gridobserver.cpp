#include "gameengine/gridobserver.h"
#include "gameengine/grid.h"

using namespace GameEngine;

GridObserver::GridObserver(Grid &grid) :
	m_source(&grid)
{
	grid.registerObserver(*this);
}

GridObserver::~GridObserver()
{
	m_source->unregisterObserver(*this);
}

const Grid &GridObserver::getGrid() const
{
	return *m_source;
}
