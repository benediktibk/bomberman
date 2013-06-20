#ifndef GAMEENGINE_ROUTERGRID_H
#define GAMEENGINE_ROUTERGRID_H

#include "gameengine/gridobserver.h"

namespace GameEngine
{
	class RouterGrid :
			public GridObserver
	{
	public:
		RouterGrid(Grid &grid);
	};
}

#endif
