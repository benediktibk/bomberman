#ifndef WALLSTATE_H
#define WALLSTATE_H

#include "point.h"

namespace Common
{
class WallState
{
public:
	void setPosition(const Point &value);
	const Point& getPosition() const;

private:
	Point m_position;
};
}

#endif
