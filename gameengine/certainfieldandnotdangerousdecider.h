#ifndef GAMEENGINE_CERTAINFIELDANDNOTDANGEROUSDECIDER_H
#define GAMEENGINE_CERTAINFIELDANDNOTDANGEROUSDECIDER_H

#include "gameengine/routergridfielddecider.h"
#include "common/gridpoint.h"
#include <vector>

namespace GameEngine
{
	class CertainFieldAndNotDangerousDecider :
			public RouterGridFieldDecider
	{
	public:
		CertainFieldAndNotDangerousDecider(const std::vector<Common::GridPoint> &possibleTargets);

		virtual bool decide(const RouterGridField &field, const RouterGridField &previousField, bool previousFieldValid) const;

	private:
		std::vector<Common::GridPoint> m_possibleTargets;
	};
}

#endif
