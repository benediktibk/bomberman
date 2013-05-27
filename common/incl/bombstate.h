#ifndef COMMON_BOMBSTATE_H
#define COMMON_BOMBSTATE_H

#include "point.h"

namespace Common
{
class BombState
{
public:
	BombState();

	void setPosition(const Point &value);
	const Point& getPosition() const;
	void setLifeTime(double time);
	double getLifeTime() const;
	void setDestructionRange(int range);
	int getDestructionRange() const;

private:
	Point m_position;
	double m_lifeTime;
	int m_destructionRange;
};
}

#endif
