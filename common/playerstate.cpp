#include "playerstate.h"
#include <assert.h>
using namespace Common;

PlayerState::PlayerState(UniqueIdCreator &creator) :
    m_direction(PlayerDirectionUp),
    m_placedBombCount(0),
    m_maxBombs(1),
    m_bombPackCount(0),
    m_speed(5.0),
    m_width(1),
    m_height(1),
    m_playerId(creator.getId()),
    m_creatorId(creator)
{}

PlayerState::PlayerState(const PlayerState &player):
    m_creatorId(player.m_creatorId)
{}

PlayerState::~PlayerState()
{
    m_creatorId.removeId(m_playerId);
}

unsigned int PlayerState::getId()
{
    return m_playerId;
}

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

void PlayerState::setMaxBombs(unsigned int maxBombs)
{
    m_maxBombs=maxBombs;
}

void PlayerState::increaseMaxBombs()
{
    m_maxBombs+=1;
}

void PlayerState::increaseMaxBombs(unsigned int number)
{
    m_maxBombs+=number;
}

void PlayerState::powerUpBombPack()
{
    m_bombPackCount+=5;
}

void PlayerState::decreaseBombPackIfPowerUp()
{
    if(m_bombPackCount>0)
        m_bombPackCount-=1;
}

void PlayerState::powerUpBombPack(unsigned int number)
{
    m_bombPackCount+=number;
}

unsigned int PlayerState::getMaxBombs() const
{
    return m_maxBombs;
}

unsigned int PlayerState::getRemainingBombs() const
{
    assert(((int)m_maxBombs-(int)m_placedBombCount)>=0);
    return m_bombPackCount+m_maxBombs-m_placedBombCount;
}

bool PlayerState::canPlayerPlaceBomb() const
{
    if(getRemainingBombs()==0)
        return false;
    else
        return true;
}

Point PlayerState::getCenterPosition() const
{
    return m_position + Point(m_width/2,m_height/2);
}
