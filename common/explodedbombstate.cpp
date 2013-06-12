#include "common/explodedbombstate.h"
#include "common/bombstate.h"

using namespace Common;

ExplodedBombState::ExplodedBombState(const BombState &bomb) :
	m_lifeTime(0.5),
	m_position(bomb.getPosition()),
	m_destructionRange(bomb.getDestructionRange())
{ }

void ExplodedBombState::decreaseLifeTime(double time)
{
	m_lifeTime -= time;
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
