#ifndef GAMEENGINE_NOTDANGEROUSANDFREEDECIDER_H
#define GAMEENGINE_NOTDANGEROUSANDFREEDECIDER_H

#include "gameengine/routergridfielddecider.h"

namespace GameEngine
{
	class NotDangerousAndFreeDecider :
			public RouterGridFieldDecider
	{
	public:
		virtual bool decide(const RouterGridField &field, const RouterGridField &previousField, bool previousFieldValid) const;
	};
}

#endif
