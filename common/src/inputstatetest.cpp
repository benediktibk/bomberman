#include "inputstatetest.h"
#include "inputstate.h"

using namespace Common;

void InputStateTest::constructor_empty_upKeyIsNotPressed()
{
	InputState inputState;

	CPPUNIT_ASSERT(!inputState.isUpKeyPressed());
}

void InputStateTest::constructor_empty_downKeyIsNotPressed()
{
    InputState inputState;

    CPPUNIT_ASSERT(!inputState.isDownKeyPressed());
}

void InputStateTest::constructor_empty_leftKeyIsNotPressed()
{
    InputState inputState;

    CPPUNIT_ASSERT(!inputState.isLeftKeyPressed());
}

void InputStateTest::constructor_empty_rightKeyIsNotPressed()
{
    InputState inputState;

    CPPUNIT_ASSERT(!inputState.isRightKeyPressed());
}

void InputStateTest::setUpKeyPressed_empty_upKeyIsPressed()
{
	InputState inputState;

	inputState.setUpKeyPressed();

	CPPUNIT_ASSERT(inputState.isUpKeyPressed());
}

void InputStateTest::setDownKeyPressed_empty_downKeyIsPressed()
{
    InputState inputState;

    inputState.setDownKeyPressed();

    CPPUNIT_ASSERT(inputState.isDownKeyPressed());
}

void InputStateTest::setLeftKeyPressed_empty_leftKeyIsPressed()
{
    InputState inputState;

    inputState.setLeftKeyPressed();

    CPPUNIT_ASSERT(inputState.isLeftKeyPressed());
}

void InputStateTest::setRightKeyPressed_empty_rightKeyIsPressed()
{
    InputState inputState;

    inputState.setRightKeyPressed();

    CPPUNIT_ASSERT(inputState.isRightKeyPressed());
}


void InputStateTest::setUpKeyNotPressed_previouslyPressed_upKeyIsNotPressed()
{
	InputState inputState;
	inputState.setUpKeyPressed();

	inputState.setUpKeyNotPressed();

	CPPUNIT_ASSERT(!inputState.isUpKeyPressed());
}

void InputStateTest::setDownKeyNotPressed_previouslyPressed_downKeyIsNotPressed()
{
    InputState inputState;
    inputState.setDownKeyPressed();

    inputState.setDownKeyNotPressed();

    CPPUNIT_ASSERT(!inputState.isDownKeyPressed());
}

void InputStateTest::setLeftKeyNotPressed_previouslyPressed_leftKeyIsNotPressed()
{
    InputState inputState;
    inputState.setLeftKeyPressed();

    inputState.setLeftKeyNotPressed();

    CPPUNIT_ASSERT(!inputState.isLeftKeyPressed());
}

void InputStateTest::setRightKeyNotPressed_previouslyPressed_rightKeyIsNotPressed()
{
    InputState inputState;
    inputState.setRightKeyPressed();

    inputState.setRightKeyNotPressed();

    CPPUNIT_ASSERT(!inputState.isRightKeyPressed());
}
