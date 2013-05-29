#include "common/changeablestatetest.h"
#include "common/changeablestate.h"

using namespace Common;

void ChangeableStateTest::constructor_empty_hasChanged()
{
	ChangeableState state;

	CPPUNIT_ASSERT(state.hasChanged());
}

void ChangeableStateTest::setChanged_wasNotChanged_hasChanged()
{
	ChangeableState state;
	state.resetChanged();

	state.setChanged();

	CPPUNIT_ASSERT(state.hasChanged());
}

void ChangeableStateTest::resetChanged_empty_hasNotChanged()
{
	ChangeableState state;

	state.resetChanged();

	CPPUNIT_ASSERT(!state.hasChanged());
}