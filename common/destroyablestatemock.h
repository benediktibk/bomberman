#ifndef COMMON_DESTROYABLESTATEMOCK_H
#define COMMON_DESTROYABLESTATEMOCK_H

#include "common/destroyablestate.h"

namespace Common
{
class DestroyableStateMock :
		public DestroyableState
{
public:
	DestroyableStateMock();

	unsigned int getCallsToShouldBeDestroyed() const;

protected:
	virtual void shouldBeDestroyed();

private:
	unsigned int m_callsToGotCallToDestroyed;
};
}

#endif
