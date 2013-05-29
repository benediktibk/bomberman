#include "playerstate.h"

using namespace Common;

PlayerState::PlayerState() :
    m_PlayerDirection(PlayerDirectionUp),
    m_placedBombCount(0),
    m_playerspeed(5.0),
    m_width(1.0),
    m_height(1.0)
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

double PlayerState::getPlayerSpeed() const
{
    return m_playerspeed;
}

double PlayerState::getPlayerHeight() const
{
    return m_height;
}

double PlayerState::getPlayerWidth() const
{
    return m_width;
}
