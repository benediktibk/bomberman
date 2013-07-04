#include "gameengine/coveredbyloosewalldecidertest.h"
#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;
using namespace Common;

void CoveredByLooseWallDeciderTest::decide_defaultField_false()
{
	RouterGridField field(GridPoint(4, 3));
	RouterGridField previousField(GridPoint(4, 3));
	CoveredByLooseWallDecider decider;

	CPPUNIT_ASSERT(!decider.decide(field, previousField, false));
}

void CoveredByLooseWallDeciderTest::decide_looseWallAtField_true()
{
	RouterGridField field(GridPoint(4, 3));
	RouterGridField previousField(GridPoint(4, 3));
	CoveredByLooseWallDecider decider;
	field.setLooseWall(true);

	CPPUNIT_ASSERT(decider.decide(field, previousField, false));
}
