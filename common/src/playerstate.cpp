#include "playerstate.h"

using namespace Common;

PlayerState::PlayerState() :
	m_position(0)
{ }

void PlayerState::setPosition(double value)
{
	m_position = value;
}

double PlayerState::getPosition() const
{
	return m_position;
}