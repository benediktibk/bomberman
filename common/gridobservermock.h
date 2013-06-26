#ifndef COMMON_GRIDOBSERVERMOCK_H
#define COMMON_GRIDOBSERVERMOCK_H

#include "common/gridobserver.h"

namespace Common
{
	class GridObserverMock :
			public GridObserver
	{
	public:
		GridObserverMock(Grid &grid);

		virtual void fieldHasChanged(const Common::GridPoint &position);

		unsigned int getCallsToFieldHasChanged() const;
		bool lastParamsOfFieldHasChangedContains(const Common::GridPoint &point) const;
		void clearLastParamsOfFieldHasChanged();
		const Common::GridPoint& getLastParamOfCallToFieldHasChanged() const;

	private:
		unsigned int m_callsToFieldHasChanged;
		std::vector<Common::GridPoint> m_lastParamsOfFieldHasChanged;
	};
}

#endif
