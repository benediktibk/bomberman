#ifndef COMMON_CHANGEABLEANDDESTROYABLESTATETEST_H
#define COMMON_CHANGEABLEANDDESTROYABLESTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class ChangeableAndDestroyableStateTest :
		public CPPUNIT_NS::TestFixture
{
public:
	CPPUNIT_TEST_SUITE(ChangeableAndDestroyableStateTest);
	CPPUNIT_TEST(setDestroyed_wasNotChanged_isChanged);
	CPPUNIT_TEST_SUITE_END();

private:
	void setDestroyed_wasNotChanged_isChanged();

};
}

#endif // CHANGEABLEANDDESTOYABLESTATETEST_H
