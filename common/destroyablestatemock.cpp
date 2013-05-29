#include "destroyablestatemock.h"

using namespace Common;

DestroyableStateMock::DestroyableStateMock() :
	m_callsToGotCallToDestroyed(0)
{ }

unsigned int DestroyableStateMock::getCallsToShouldBeDestroyed() const
{
	return m_callsToGotCallToDestroyed;
}

void DestroyableStateMock::shouldBeDestroyed()
{
	++m_callsToGotCallToDestroyed;
}
