#include "bombstate.h"

using namespace Common;

BombState::BombState(UniqueIdCreator &creator) :
    m_lifeTime(3),
    m_destructionRange(1),
    m_bombid(creator.getId()),
    m_creatorid(creator)
{ }
BombState::~BombState()
{
    m_creatorid.removeId(m_bombid);
}

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

double BombState::getLifeTime() const
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
