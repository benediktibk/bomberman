#include "common/gridobservermock.h"

using namespace Common;

GridObserverMock::GridObserverMock(Grid &grid) :
	GridObserver(grid),
	m_callsToFieldHasChanged(0)
{ }

void GridObserverMock::fieldHasChanged(const GridPoint &position)
{
	m_lastParamOfCallToFieldHasChanged = position;
	++m_callsToFieldHasChanged;
}

unsigned int GridObserverMock::getCallsToFieldHasChanged() const
{
	return m_callsToFieldHasChanged;
}

const GridPoint &GridObserverMock::getLastParamOfCallToFieldHasChanged() const
{
	return m_lastParamOfCallToFieldHasChanged;
}
