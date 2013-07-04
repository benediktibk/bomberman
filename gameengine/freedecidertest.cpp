#include "gameengine/freedecidertest.h"
#include "gameengine/freedecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

void FreeDeciderTest::decide_defaultField_true()
{
	FreeDecider decider;
	RouterGridField previousField;
	RouterGridField field;

	CPPUNIT_ASSERT(decider.decide(field, previousField, false));
}

void FreeDeciderTest::decide_solidWallAtField_false()
{
	FreeDecider decider;
	RouterGridField previousField;
	RouterGridField field;

	field.setSolidWall(true);

	CPPUNIT_ASSERT(!decider.decide(field, previousField, false));
}
