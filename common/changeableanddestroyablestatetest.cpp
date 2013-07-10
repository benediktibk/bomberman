#include "changeableanddestroyablestatetest.h"
#include "changeableanddestroyablestate.h"

using namespace Common;

void Common::ChangeableAndDestroyableStateTest::setDestroyed_wasNotChanged_isChanged()
{
	ChangeableAndDestroyableState state;
	state.setDestroyed();

	CPPUNIT_ASSERT(state.hasChanged());
}
