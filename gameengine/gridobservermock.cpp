#include "gameengine/gridobservermock.h"

using namespace GameEngine;
using namespace Common;

GridObserverMock::GridObserverMock(Grid &grid) :
	GridObserver(grid),
	m_callsToFieldHasChanged(0)
{ }

void GridObserverMock::fieldHasChanged(const GridPoint &)
{
	++m_callsToFieldHasChanged;
}

unsigned int GridObserverMock::getCallsToFieldHasChanged() const
{
	return m_callsToFieldHasChanged;
}
