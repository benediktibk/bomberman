#ifndef COMMON_INPUTSTATETEST_H
#define COMMON_INPUTSTATETEST_H

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
	 CPPUNIT_TEST(isMovementButtonPressed_upKeyPressed_true);
	 CPPUNIT_TEST(isMovementButtonPressed_downKeyPressed_true);
	 CPPUNIT_TEST(isMovementButtonPressed_leftKeyPressed_true);
	 CPPUNIT_TEST(isMovementButtonPressed_rightKeyPressed_true);
	 CPPUNIT_TEST(isMovementButtonPressed_noButtonPressed_false);
	 CPPUNIT_TEST(isMoreThanOneMovementButtonPressed_upAndDownPressed_true);
	 CPPUNIT_TEST(isMoreThanOneMovementButtonPressed_upPressed_false);
	 CPPUNIT_TEST(isMoreThanOneMovementButtonPressed_leftAndRightPressed_true);
	 CPPUNIT_TEST(isMoreThanOneMovementButtonPressed_upAndDownAndLeftPressed_true);
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
	 void isMovementButtonPressed_upKeyPressed_true();
	 void isMovementButtonPressed_downKeyPressed_true();
	 void isMovementButtonPressed_leftKeyPressed_true();
	 void isMovementButtonPressed_rightKeyPressed_true();
	 void isMovementButtonPressed_noButtonPressed_false();
	 void isMoreThanOneMovementButtonPressed_upAndDownPressed_true();
	 void isMoreThanOneMovementButtonPressed_upPressed_false();
	 void isMoreThanOneMovementButtonPressed_leftAndRightPressed_true();
	 void isMoreThanOneMovementButtonPressed_upAndDownAndLeftPressed_true();
};
}

#endif
