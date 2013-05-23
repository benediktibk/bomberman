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

private:
	Point m_position;
};
}

#endif
