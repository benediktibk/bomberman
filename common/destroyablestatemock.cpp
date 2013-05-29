#include "destroyablestatemock.h"

using namespace Common;

DestroyableStateMock::DestroyableStateMock() :
	m_callsToGotCallToDestroyed(0)
{ }

unsigned int DestroyableStateMock::getCallsToGotCallToDestroyed() const
{
	return m_callsToGotCallToDestroyed;
}

void DestroyableStateMock::gotCallToDestroyed()
{
	++m_callsToGotCallToDestroyed;
}
