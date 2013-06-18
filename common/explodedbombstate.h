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
		ExplodedBombState(	const BombState &bomb,
							unsigned int destructionRangeLeft, unsigned int destructionRangeUp,
							unsigned int destructionRangeRight, unsigned int destructionRangeDown);

		void decreaseLifeTime(double time);
		double getLifeTime() const;
		unsigned int getMaximumDestructionRange() const;
		unsigned int getDestructionRangeLeft() const;
		unsigned int getDestructionRangeUp() const;
		unsigned int getDestructionRangeRight() const;
		unsigned int getDestructionRangeDown() const;
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
		unsigned int m_destructionRangeLeft;
		unsigned int m_destructionRangeUp;
		unsigned int m_destructionRangeRight;
		unsigned int m_destructionRangeDown;
		double m_height;
		double m_width;
	};
}

#endif
