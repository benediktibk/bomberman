#include "playerstate.h"

using namespace Common;

PlayerState::PlayerState() :
    m_position(0),
    m_PlayerDirection(PlayerDirectionUp)
{ }

void PlayerState::setPosition(double value)
{
	m_position = value;
}

double PlayerState::getPosition() const
{
	return m_position;
}

void PlayerState::setDirectionUp()
{
    m_PlayerDirection=PlayerDirectionUp;
}

void PlayerState::setDirectionDown()
{
    m_PlayerDirection=PlayerDirectionDown;
}

void PlayerState::setDirectionLeft()
{
    m_PlayerDirection=PlayerDirectionLeft;
}

void PlayerState::setDirectionRight()
{
    m_PlayerDirection=PlayerDirectionRight;
}

PlayerState::PlayerDirection PlayerState::getDirection() const
{
    return m_PlayerDirection;
}
