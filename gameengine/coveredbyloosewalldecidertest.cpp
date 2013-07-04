#include "gameengine/coveredbyloosewalldecidertest.h"
#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

void CoveredByLooseWallDeciderTest::decide_defaultField_false()
{
	RouterGridField field;
	RouterGridField previousField;
	CoveredByLooseWallDecider decider;

	CPPUNIT_ASSERT(!decider.decide(field, previousField, false));
}

void CoveredByLooseWallDeciderTest::decide_looseWallAtField_true()
{
	RouterGridField field;
	RouterGridField previousField;
	CoveredByLooseWallDecider decider;
	field.setLooseWall(true);

	CPPUNIT_ASSERT(decider.decide(field, previousField, false));
}
