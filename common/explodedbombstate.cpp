#include "common/explodedbombstate.h"
#include "common/bombstate.h"
#include <assert.h>

using namespace Common;

ExplodedBombState::ExplodedBombState(
		const BombState &bomb,
		unsigned int destructionRangeLeft, unsigned int destructionRangeUp,
		unsigned int destructionRangeRight, unsigned int destructionRangeDown) :
	m_lifeTime(initialLifeTime()),
	m_position(bomb.getPosition()),
	m_maximumDestructionRange(bomb.getDestructionRange()),
	m_destructionRangeLeft(destructionRangeLeft),
	m_destructionRangeUp(destructionRangeUp),
	m_destructionRangeRight(destructionRangeRight),
	m_destructionRangeDown(destructionRangeDown),
	m_height(bomb.getHeight()),
	m_width(bomb.getWidth())
{
	assert(m_destructionRangeLeft <= m_maximumDestructionRange);
	assert(m_destructionRangeUp <= m_maximumDestructionRange);
	assert(m_destructionRangeRight <= m_maximumDestructionRange);
	assert(m_destructionRangeDown <= m_maximumDestructionRange);
}

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

double ExplodedBombState::getWidth() const
{
	return m_width;
}

double ExplodedBombState::getHeight() const
{
	return m_height;
}

double ExplodedBombState::initialLifeTime()
{
	return 0.5;
}
