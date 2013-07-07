#include "common/explodedbombstate.h"
#include "common/bombstate.h"
#include <assert.h>

using namespace Common;

ExplodedBombState::ExplodedBombState(const BombState &bomb) :
	m_lifeTime(initialLifeTime()),
	m_position(bomb.getPosition()),
	m_maximumDestructionRange(bomb.getDestructionRange()),
	m_destructionRangeLeft(m_maximumDestructionRange),
	m_destructionRangeUp(m_maximumDestructionRange),
	m_destructionRangeRight(m_maximumDestructionRange),
	m_destructionRangeDown(m_maximumDestructionRange),
	m_dimension(bomb.getDimension())
{ }

void ExplodedBombState::decreaseLifeTime(double time)
{
	m_lifeTime -= time;
	setChanged();
}

double ExplodedBombState::getLifeTime() const
{
	return m_lifeTime;
}

unsigned int ExplodedBombState::getMaximumDestructionRange() const
{
	return m_maximumDestructionRange;
}

void ExplodedBombState::setDestructionRangeLeft(unsigned int value)
{
	assert(value <= m_maximumDestructionRange);
	m_destructionRangeLeft = value;
}

void ExplodedBombState::setDestructionRangeUp(unsigned int value)
{
	assert(value <= m_maximumDestructionRange);
	m_destructionRangeUp = value;
}

void ExplodedBombState::setDestructionRangeRight(unsigned int value)
{
	assert(value <= m_maximumDestructionRange);
	m_destructionRangeRight = value;
}

void ExplodedBombState::setDestructionRangeDown(unsigned int value)
{
	assert(value <= m_maximumDestructionRange);
	m_destructionRangeDown = value;
}

unsigned int ExplodedBombState::getDestructionRangeLeft() const
{
	return m_destructionRangeLeft;
}

unsigned int ExplodedBombState::getDestructionRangeUp() const
{
	return m_destructionRangeUp;
}

unsigned int ExplodedBombState::getDestructionRangeRight() const
{
	return m_destructionRangeRight;
}

unsigned int ExplodedBombState::getDestructionRangeDown() const
{
	return m_destructionRangeDown;
}

void ExplodedBombState::setDestroyedIfNoLifeTimeLeft()
{
	if (m_lifeTime <= 0)
		setDestroyed();
}

const Point &ExplodedBombState::getPosition() const
{
	return m_position;
}

double ExplodedBombState::getDimension() const
{
	return m_dimension;
}

double ExplodedBombState::initialLifeTime()
{
	return 10.0;
}
