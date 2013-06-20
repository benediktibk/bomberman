#ifndef GAMEENGINE_GRIDOBSERVERMOCK_H
#define GAMEENGINE_GRIDOBSERVERMOCK_H

#include "gameengine/gridobserver.h"

namespace GameEngine
{
	class GridObserverMock :
			public GridObserver
	{
	public:
		GridObserverMock(Grid &grid);

		virtual void fieldHasChanged(const Common::GridPoint &position);

		unsigned int getCallsToFieldHasChanged() const;
		const Common::GridPoint& getLastParamOfCallToFieldHasChanged() const;

	private:
		unsigned int m_callsToFieldHasChanged;
		Common::GridPoint m_lastParamOfCallToFieldHasChanged;
	};
}

#endif
