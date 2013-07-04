#include "gameengine/freedecidertest.h"
#include "gameengine/freedecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;
using namespace Common;

void FreeDeciderTest::decide_defaultField_true()
{
	FreeDecider decider;
	RouterGridField previousField(GridPoint(4, 3));
	RouterGridField field(GridPoint(4, 3));

	CPPUNIT_ASSERT(decider.decide(field, previousField, false));
}

void FreeDeciderTest::decide_solidWallAtField_false()
{
	FreeDecider decider;
	RouterGridField previousField(GridPoint(4, 3));
	RouterGridField field(GridPoint(4, 3));

	field.setSolidWall(true);

	CPPUNIT_ASSERT(!decider.decide(field, previousField, false));
}
