#include "gameengine/notdangerousandfreedecidertest.h"
#include "gameengine/notdangerousandfreedecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;
using namespace Common;

void NotDangerousAndFreeDeciderTest::decide_dangerousField_false()
{
	RouterGridField field(GridPoint(4, 3));
	RouterGridField previousField(GridPoint(4, 3));
	NotDangerousAndFreeDecider decider;
	field.setDangerous(true);

	CPPUNIT_ASSERT(!decider.decide(field, previousField, false));
}

void NotDangerousAndFreeDeciderTest::decide_wallAtField_false()
{
	RouterGridField field(GridPoint(4, 3));
	RouterGridField previousField(GridPoint(4, 3));
	NotDangerousAndFreeDecider decider;
	field.setLooseWall(true);

	CPPUNIT_ASSERT(!decider.decide(field, previousField, false));
}

void NotDangerousAndFreeDeciderTest::decide_notDangerousAndFree_true()
{
	RouterGridField field(GridPoint(4, 3));
	RouterGridField previousField(GridPoint(4, 3));
	NotDangerousAndFreeDecider decider;

	CPPUNIT_ASSERT(decider.decide(field, previousField, false));
}
