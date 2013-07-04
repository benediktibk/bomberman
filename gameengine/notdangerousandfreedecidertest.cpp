#include "gameengine/notdangerousandfreedecidertest.h"
#include "gameengine/notdangerousandfreedecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

void NotDangerousAndFreeDeciderTest::decide_dangerousField_false()
{
	RouterGridField field;
	RouterGridField previousField;
	NotDangerousAndFreeDecider decider;
	field.setDangerous(true);

	CPPUNIT_ASSERT(!decider.decide(field, previousField, false));
}

void NotDangerousAndFreeDeciderTest::decide_wallAtField_false()
{
	RouterGridField field;
	RouterGridField previousField;
	NotDangerousAndFreeDecider decider;
	field.setLooseWall(true);

	CPPUNIT_ASSERT(!decider.decide(field, previousField, false));
}

void NotDangerousAndFreeDeciderTest::decide_notDangerousAndFree_true()
{
	RouterGridField field;
	RouterGridField previousField;
	NotDangerousAndFreeDecider decider;

	CPPUNIT_ASSERT(decider.decide(field, previousField, false));
}
