#ifndef GAMEENGINE_GRIDOBSERVER_H
#define GAMEENGINE_GRIDOBSERVER_H

#include "common/gridpoint.h"

namespace GameEngine
{
	class Grid;

	class GridObserver
	{
	public:
		GridObserver(Grid &grid);
		virtual ~GridObserver();

		virtual void fieldHasChanged(const Common::GridPoint &position) = 0;

	protected:
		const Grid& getGrid() const;

	private:
		Grid * const m_source;
	};
}

#endif
