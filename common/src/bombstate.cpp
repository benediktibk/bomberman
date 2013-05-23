#include "bombstate.h"

using namespace Common;

void BombState::setPosition(const Point &value)
{
	m_position = value;
}

const Point &BombState::getPosition() const
{
	return m_position;
}

