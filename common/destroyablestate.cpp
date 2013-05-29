#include "destroyablestate.h"

using namespace Common;

DestroyableState::DestroyableState() :
	m_destroyed(false)
{ }

bool DestroyableState::isDestroyed() const
{
	return m_destroyed;
}

void DestroyableState::setDestroyed()
{
	m_destroyed = true;
}

