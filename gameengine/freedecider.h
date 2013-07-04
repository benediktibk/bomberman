#ifndef GAMEENGINE_FREEDECIDER_H
#define GAMEENGINE_FREEDECIDER_H

#include "gameengine/routergridfielddecider.h"

namespace GameEngine
{
	class FreeDecider :
			public RouterGridFieldDecider
	{
	public:
		virtual bool decide(const RouterGridField &field, const RouterGridField &previousField, bool previousFieldValid) const;
	};
}

#endif
