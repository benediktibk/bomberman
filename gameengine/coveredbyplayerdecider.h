#ifndef GAMEENGINE_COVEREDBYPLAYERDECIDER_H
#define GAMEENGINE_COVEREDBYPLAYERDECIDER_H

#include "gameengine/routergridfielddecider.h"

namespace GameEngine
{
	class Router;

	class CoveredByPlayerDecider :
			public RouterGridFieldDecider
	{
	public:
		CoveredByPlayerDecider(const Router &router, unsigned int bombRange, bool considerEscape);

		virtual bool decide(const RouterGridField &field, const RouterGridField &previousField, bool previousFieldValid) const;

	private:
		const Router &m_router;
		unsigned int m_bombRange;
		bool m_considerEscape;
	};
}

#endif
