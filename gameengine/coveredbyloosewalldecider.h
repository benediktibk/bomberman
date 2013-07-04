#ifndef GAMEENGINE_COVEREDBYLOOSEWALLDECIDER_H
#define GAMEENGINE_COVEREDBYLOOSEWALLDECIDER_H

#include "gameengine/routergridfielddecider.h"

namespace GameEngine
{
	class Router;

	class CoveredByLooseWallDecider :
			public RouterGridFieldDecider
	{
	public:
		CoveredByLooseWallDecider(const Router &router, unsigned int bombRange, bool considerEscape);

		virtual bool decide(const RouterGridField &field, const RouterGridField &previousField, bool previousFieldValid) const;

	private:
		const Router &m_router;
		unsigned int m_bombRange;
		bool m_considerEscape;
	};
}

#endif
