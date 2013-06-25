#include "common/gridobserver.h"
#include "common/grid.h"

using namespace Common;

GridObserver::GridObserver(Grid &grid) :
	m_source(&grid)
{
	grid.registerObserver(*this);
}

GridObserver::~GridObserver()
{
	m_source->unregisterObserver(*this);
}
