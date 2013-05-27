#ifndef COMMON_ENEMYSTATE_H
#define COMMON_ENEMYSTATE_H

#include "point.h"

namespace Common
{
class EnemyState
{
public:
	void setPosition(const Point &value);
	const Point& getPosition() const;

private:
	Point m_position;
};
}

#endif
