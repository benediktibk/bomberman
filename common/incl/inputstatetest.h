#ifndef INPUTSTATETEST_H
#define INPUTSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class InputStateTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(InputStateTest);
	 CPPUNIT_TEST(constructor_empty_upKeyIsNotPressed);
	 CPPUNIT_TEST(setUpKeyPressed_empty_upKeyIsPressed);
	 CPPUNIT_TEST(setUpKeyNotPressed_previouslyPressed_upKeyIsNotPressed);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void constructor_empty_upKeyIsNotPressed();
	 void setUpKeyPressed_empty_upKeyIsPressed();
	 void setUpKeyNotPressed_previouslyPressed_upKeyIsNotPressed();
};
}

#endif
