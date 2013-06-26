#include "common/gridobservermock.h"
#include <algorithm>
#include <assert.h>

using namespace Common;

GridObserverMock::GridObserverMock(Grid &grid) :
	GridObserver(grid),
	m_callsToFieldHasChanged(0)
{ }

void GridObserverMock::fieldHasChanged(const GridPoint &position)
{
	m_lastParamsOfFieldHasChanged.push_back(position);
	++m_callsToFieldHasChanged;
}

unsigned int GridObserverMock::getCallsToFieldHasChanged() const
{
	return m_callsToFieldHasChanged;
}

bool GridObserverMock::lastParamsOfFieldHasChangedContains(const GridPoint &point) const
{
	return count(m_lastParamsOfFieldHasChanged.begin(), m_lastParamsOfFieldHasChanged.end(), point) > 0;
}

void GridObserverMock::clearLastParamsOfFieldHasChanged()
{
	m_lastParamsOfFieldHasChanged.clear();
}

const GridPoint &GridObserverMock::getLastParamOfCallToFieldHasChanged() const
{
	assert(m_lastParamsOfFieldHasChanged.size() > 0);
	return m_lastParamsOfFieldHasChanged.back();
}
