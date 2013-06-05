#include "bombstate.h"

using namespace Common;

BombState::BombState(UniqueIdCreator &creator) :
	m_lifeTime(3.0),
	m_width(1.0),
	m_height(1.0),
	m_destructionRange(1),
	m_bombId(creator.getId()),
	m_creatorId(creator)
{ }

BombState::~BombState()
{
	m_creatorId.removeId(m_bombId);
}

void BombState::setPosition(const Point &value)
{
	m_position = value;
	setChanged();
}

const Point &BombState::getPosition() const
{
	return m_position;
}

void BombState::setLifeTime(double time)
{
	m_lifeTime = time;
	setChanged();
}

double BombState::getLifeTime() const
{
	return m_lifeTime;
}
void BombState::setDestructionRange(int range)
{
	m_destructionRange = range;
	setChanged();
}

unsigned int BombState::getDestructionRange() const
{
	return m_destructionRange;
}

unsigned int BombState::getBombId() const
{
	return m_bombId;
}

double BombState::getHeight() const
{
	return m_height;
}

double BombState::getWidth() const
{
	return m_width;
}

void BombState::shouldBeDestroyed()
{
	setChanged();
}
