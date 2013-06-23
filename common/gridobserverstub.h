#ifndef COMMON_GRIDOBSERVERSTUB_H
#define COMMON_GRIDOBSERVERSTUB_H

#include "common/gridobserver.h"

namespace Common
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
