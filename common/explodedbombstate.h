#ifndef COMMON_EXPLODEDBOMBSTATE_H
#define COMMON_EXPLODEDBOMBSTATE_H

#include "common/point.h"
#include "common/changeablestate.h"
#include "common/destroyablestate.h"

namespace Common
{
	class BombState;

	class ExplodedBombState :
			public ChangeableState,
			public DestroyableState
	{
	public:
		ExplodedBombState(const BombState &bomb);

		void decreaseLifeTime(double time);
		double getLifeTime() const;
		unsigned int getDesructionRange() const;
		void setDestroyedIfNoLifeTimeLeft();
		const Point& getPosition() const;

	private:
		double m_lifeTime;
		Point m_position;
		unsigned int m_destructionRange;
	};
}

#endif
