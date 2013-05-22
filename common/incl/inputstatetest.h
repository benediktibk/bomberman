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
     CPPUNIT_TEST(constructor_empty_downKeyIsNotPressed);
     CPPUNIT_TEST(constructor_empty_leftKeyIsNotPressed);
     CPPUNIT_TEST(constructor_empty_rightKeyIsNotPressed);
	 CPPUNIT_TEST(setUpKeyPressed_empty_upKeyIsPressed);
     CPPUNIT_TEST(setDownKeyPressed_empty_downKeyIsPressed);
     CPPUNIT_TEST(setLeftKeyPressed_empty_leftKeyIsPressed);
     CPPUNIT_TEST(setRightKeyPressed_empty_rightKeyIsPressed);
	 CPPUNIT_TEST(setUpKeyNotPressed_previouslyPressed_upKeyIsNotPressed);
     CPPUNIT_TEST(setDownKeyNotPressed_previouslyPressed_downKeyIsNotPressed);
     CPPUNIT_TEST(setLeftKeyNotPressed_previouslyPressed_leftKeyIsNotPressed);
     CPPUNIT_TEST(setRightKeyNotPressed_previouslyPressed_rightKeyIsNotPressed);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void constructor_empty_upKeyIsNotPressed();
	 void setUpKeyPressed_empty_upKeyIsPressed();
     void setUpKeyNotPressed_previouslyPressed_upKeyIsNotPressed();
     void constructor_empty_downKeyIsNotPressed();
     void setDownKeyPressed_empty_downKeyIsPressed();
     void setDownKeyNotPressed_previouslyPressed_downKeyIsNotPressed();
     void constructor_empty_leftKeyIsNotPressed();
     void setLeftKeyPressed_empty_leftKeyIsPressed();
     void setLeftKeyNotPressed_previouslyPressed_leftKeyIsNotPressed();
     void constructor_empty_rightKeyIsNotPressed();
     void setRightKeyPressed_empty_rightKeyIsPressed();
     void setRightKeyNotPressed_previouslyPressed_rightKeyIsNotPressed();
};
}

#endif
