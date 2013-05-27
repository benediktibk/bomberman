#include "bombstate.h"

using namespace Common;

BombState::BombState() :
    m_lifeTime(3000),
    m_destructionRange(1)
{ }

void BombState::setPosition(const Point &value)
{
	m_position = value;
}

const Point &BombState::getPosition() const
{
	return m_position;
}

void BombState::setLifeTime(double time)
{
    m_lifeTime = time;
}

double BombState::getLifeTime()
{
    return m_lifeTime;
}
void BombState::setDestructionRange(int range)
{
    m_destructionRange = range;
}

int BombState::getDestructionRange() const
{
    return m_destructionRange;
}
