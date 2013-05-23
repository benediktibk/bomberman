#include "enemystate.h"

using namespace Common;

void EnemyState::setPosition(const Point &value)
{
	m_position = value;
}

const Point &EnemyState::getPosition() const
{
	return m_position;
}
