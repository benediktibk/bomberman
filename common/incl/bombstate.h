#ifndef BOMBSTATE_H
#define BOMBSTATE_H

#include "point.h"

namespace Common
{
class BombState
{
public:
	void setPosition(const Point &value);
	const Point& getPosition() const;
    void setLifeTime(double time);
    double getLifeTime();

private:
	Point m_position;
    double m_lifeTime;
};
}

#endif
