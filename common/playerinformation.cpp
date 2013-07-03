#include "playerinformation.h"

using namespace Common;
using namespace std;


PlayerInformation::PlayerInformation()
{
}

PlayerInformation::~PlayerInformation()
{
}

void PlayerInformation::setBombCounter(unsigned int amount)
{
    m_bombCounter = amount;
}

unsigned int PlayerInformation::getBombCounter() const
{
    return m_bombCounter;
}

void PlayerInformation::setRangeCounter(unsigned int amount)
{
    m_rangeCounter = amount;
}

unsigned int PlayerInformation::getRangeCounter() const
{
    return m_rangeCounter;
}

void PlayerInformation::setSpeedCounter(double amount)
{
    m_speedCounter = static_cast<unsigned int>  (amount*2-3);
}

unsigned int PlayerInformation::getSpeedCounter() const
{
    return m_speedCounter;
}

void PlayerInformation::setPlayerId(unsigned int id)
{
    m_playerId = id;
}

unsigned int PlayerInformation::getPlayerId() const
{
    return m_playerId+1;
}

