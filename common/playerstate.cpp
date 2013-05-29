#include "playerstate.h"

using namespace Common;

PlayerState::PlayerState() :
	m_direction(PlayerDirectionUp),
	m_placedBombCount(0),
	m_speed(5.0),
	m_width(1),
	m_height(1)
{ }

void PlayerState::setPosition(Point value)
{
	m_position = value;
}

Point PlayerState::getPosition() const
{
	return m_position;
}

void PlayerState::setDirectionUp()
{
	m_direction=PlayerDirectionUp;
}

void PlayerState::setDirectionDown()
{
	m_direction=PlayerDirectionDown;
}

void PlayerState::setDirectionLeft()
{
	m_direction=PlayerDirectionLeft;
}

void PlayerState::setDirectionRight()
{
	m_direction=PlayerDirectionRight;
}

PlayerState::PlayerDirection PlayerState::getDirection() const
{
	return m_direction;
}

void PlayerState::countBomb()
{
	m_placedBombCount += 1;
}

void PlayerState::reduceBombCount()
{
	m_placedBombCount -= 1;
}

unsigned int PlayerState::getBombCount()
{
	return m_placedBombCount;
}

double PlayerState::getSpeed() const
{
	return m_speed;
}

double PlayerState::getHeight() const
{
	return m_height;
}

double PlayerState::getWidth() const
{
	return m_width;
}
