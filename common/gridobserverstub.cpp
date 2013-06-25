#include "common/gridobserverstub.h"

using namespace Common;

GridObserverStub::GridObserverStub(Grid &grid) :
	GridObserver(grid)
{ }

void GridObserverStub::fieldHasChanged(const Common::GridPoint &)
{ }
