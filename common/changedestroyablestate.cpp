#include "common/changedestroyablestate.h"

using namespace Common;

ChangeDestroyableState::ChangeDestroyableState():
    m_destroyed(false),
    m_changed(true)
{ }

ChangeDestroyableState::~ChangeDestroyableState()
{ }

void ChangeDestroyableState::setChanged()
{
	m_changed = true;
}

bool ChangeDestroyableState::hasChanged()
{
	return m_changed;
}

void ChangeDestroyableState::resetChanged()
{
	m_changed = false;
}

bool ChangeDestroyableState::isDestroyed() const
{
	return m_destroyed;
}

void ChangeDestroyableState::setDestroyed()
{
	m_destroyed = true;
	m_changed = true;
}
