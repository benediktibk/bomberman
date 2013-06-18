#include "common/explodedbombstate.h"
#include "common/bombstate.h"

using namespace Common;

ExplodedBombState::ExplodedBombState(const BombState &bomb) :
	m_lifeTime(initialLifeTime()),
	m_position(bomb.getPosition()),
	m_destructionRange(bomb.getDestructionRange()),
	m_height(bomb.getHeight()),
	m_width(bomb.getWidth())
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

unsigned int ExplodedBombState::getDesructionRange() const
{
	return m_destructionRange;
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
