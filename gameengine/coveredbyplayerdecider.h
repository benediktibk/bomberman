#ifndef GAMEENGINE_COVEREDBYPLAYERDECIDER_H
#define GAMEENGINE_COVEREDBYPLAYERDECIDER_H

#include "gameengine/routergridfielddecider.h"

namespace GameEngine
{
	class CoveredByPlayerDecider :
			public RouterGridFieldDecider
	{
	public:
		virtual bool decide(const RouterGridField &field, const RouterGridField &previousField, bool previousFieldValid) const;
	};
}

#endif
