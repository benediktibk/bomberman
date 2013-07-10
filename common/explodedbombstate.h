#ifndef COMMON_EXPLODEDBOMBSTATE_H
#define COMMON_EXPLODEDBOMBSTATE_H

#include "common/point.h"
#include "common/changeableanddestroyablestate.h"

namespace Common
{
	class BombState;

	class ExplodedBombState :
			public ChangeableAndDestroyableState
	{
	public:
		ExplodedBombState(const BombState &bomb);

		void decreaseLifeTime(double time);
		double getLifeTime() const;
		unsigned int getMaximumDestructionRange() const;
		void setDestructionRangeLeft(unsigned int value);
		void setDestructionRangeUp(unsigned int value);
		void setDestructionRangeRight(unsigned int value);
		void setDestructionRangeDown(unsigned int value);
		unsigned int getDestructionRangeLeft() const;
		unsigned int getDestructionRangeUp() const;
		unsigned int getDestructionRangeRight() const;
		unsigned int getDestructionRangeDown() const;
		void setDestroyedIfNoLifeTimeLeft();
		const Point& getPosition() const;
		double getDimension() const;

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
		const double m_dimension;
	};
}

#endif
