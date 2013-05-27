#include "wallstate.h"

using namespace Common;

void WallState::setPosition(const Point &value)
{
	m_position = value;
}

const Point &WallState::getPosition() const
{
	return m_position;
}
