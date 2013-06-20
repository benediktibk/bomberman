#include "gameengine/routergrid.h"
#include "gameengine/grid.h"

using namespace GameEngine;

RouterGrid::RouterGrid(Grid &grid) :
	GridObserver(grid)
{ }
