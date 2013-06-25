#ifndef COMMON_GRIDOBSERVER_H
#define COMMON_GRIDOBSERVER_H

#include "common/gridpoint.h"

namespace Common
{
	class Grid;

	class GridObserver
	{
	public:
		GridObserver(Grid &grid);
		virtual ~GridObserver();

		virtual void fieldHasChanged(const Common::GridPoint &position) = 0;

	private:
		Grid * const m_source;
	};
}

#endif
