#ifndef GAMEENGINE_COVEREDBYLOOSEWALLDECIDER_H
#define GAMEENGINE_COVEREDBYLOOSEWALLDECIDER_H

#include "gameengine/routergridfielddecider.h"

namespace GameEngine
{
	class CoveredByLooseWallDecider :
			public RouterGridFieldDecider
	{
	public:
		virtual bool decide(const RouterGridField &field) const;
	};
}

#endif
