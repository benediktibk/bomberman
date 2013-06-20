#ifndef GAMEENGINE_GRIDOBSERVERSTUB_H
#define GAMEENGINE_GRIDOBSERVERSTUB_H

#include "gameengine/gridobserver.h"

namespace GameEngine
{
	class GridObserverStub :
			public GridObserver
	{
	public:
		GridObserverStub(Grid &grid);

		virtual void fieldHasChanged(const Common::GridPoint &position);
	};
}

#endif
