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
		CoveredByPlayerDecider(const Router &router, unsigned int bombRange, double speed, double bombLifeTime, bool considerEscape);

		virtual bool decide(const RouterGridField &field, const RouterGridField &previousField, bool previousFieldValid) const;

	private:
		const Router &m_router;
		unsigned int m_bombRange;
		double m_speed;
		double m_bombLifeTime;
		bool m_considerEscape;
	};
}

#endif
