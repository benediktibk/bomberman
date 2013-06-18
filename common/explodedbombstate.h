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
		unsigned int getMaximumDestructionRange() const;
		void setDestroyedIfNoLifeTimeLeft();
		const Point& getPosition() const;
		double getWidth() const;
		double getHeight() const;

	public:
		static double initialLifeTime();

	private:
		// forbid copies
		ExplodedBombState(const ExplodedBombState &);
		void operator=(const ExplodedBombState &);

	private:
		double m_lifeTime;
		Point m_position;
		unsigned int m_maximumDestructionRange;
		double m_height;
		double m_width;
	};
}

#endif
