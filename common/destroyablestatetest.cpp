#include "destroyablestatetest.h"
#include "destroyablestate.h"

using namespace Common;

void DestroyableStateTest::constructor_empty_notDestroyed()
{
	DestroyableState state;

	CPPUNIT_ASSERT(!state.isDestroyed());
}

void DestroyableStateTest::setDestroyed_empty_isDestroyed()
{
	DestroyableState state;

	state.setDestroyed();

	CPPUNIT_ASSERT(state.isDestroyed());
}
