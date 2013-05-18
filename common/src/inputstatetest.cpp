#include "inputstatetest.h"
#include "inputstate.h"

using namespace Common;

void InputStateTest::constructor_empty_upKeyIsNotPressed()
{
	InputState inputState;

	CPPUNIT_ASSERT(!inputState.isUpKeyPressed());
}

void InputStateTest::setUpKeyPressed_empty_upKeyIsPressed()
{
	InputState inputState;

	inputState.setUpKeyPressed();

	CPPUNIT_ASSERT(inputState.isUpKeyPressed());
}

void InputStateTest::setUpKeyNotPressed_previouslyPressed_upKeyIsNotPressed()
{
	InputState inputState;
	inputState.setUpKeyPressed();

	inputState.setUpKeyNotPressed();

	CPPUNIT_ASSERT(!inputState.isUpKeyPressed());
}
