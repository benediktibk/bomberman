#ifndef CHANGEABLESTATETEST_H
#define CHANGEABLESTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class ChangeableStateTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(ChangeableStateTest);
	 CPPUNIT_TEST(constructor_empty_hasChanged);
	 CPPUNIT_TEST(setChanged_wasNotChanged_hasChanged);
	 CPPUNIT_TEST(resetChanged_empty_hasNotChanged);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void constructor_empty_hasChanged();
	 void setChanged_wasNotChanged_hasChanged();
	 void resetChanged_empty_hasNotChanged();
};
}

#endif
