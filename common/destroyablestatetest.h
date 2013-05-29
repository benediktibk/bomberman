#ifndef COMMON_DESTROYABLESTATETEST_H
#define COMMON_DESTROYABLESTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class DestroyableStateTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(DestroyableStateTest);
	 CPPUNIT_TEST(constructor_empty_notDestroyed);
	 CPPUNIT_TEST(setDestroyed_empty_isDestroyed);
	 CPPUNIT_TEST(setDestroyed_onMockState_gotOneCallToGotDestroyed);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void constructor_empty_notDestroyed();
	 void setDestroyed_empty_isDestroyed();
	 void setDestroyed_onMockState_gotOneCallToGotDestroyed();
};
}

#endif
