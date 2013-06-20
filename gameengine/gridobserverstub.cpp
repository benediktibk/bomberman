#include "gameengine/gridobserverstub.h"

using namespace GameEngine;

GridObserverStub::GridObserverStub(Grid &grid) :
	GridObserver(grid)
{ }

void GridObserverStub::fieldHasChanged(const Common::GridPoint &)
{ }
