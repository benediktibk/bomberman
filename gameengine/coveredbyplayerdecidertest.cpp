#include "gameengine/coveredbyplayerdecidertest.h"
#include "gameengine/coveredbyplayerdecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;
using namespace Common;

void GameEngine::CoveredByPlayerDeciderTest::decide_defaultField_false()
{
	RouterGridField field(GridPoint(4, 3));
	RouterGridField previousField(GridPoint(4, 3));
	CoveredByPlayerDecider decider;

	CPPUNIT_ASSERT(!decider.decide(field, previousField, false));
}

void GameEngine::CoveredByPlayerDeciderTest::decide_playerAtField_true()
{
	RouterGridField field(GridPoint(4, 3));
	RouterGridField previousField(GridPoint(4, 3));
	CoveredByPlayerDecider decider;
	field.setPlayer(true);

	CPPUNIT_ASSERT(decider.decide(field, previousField, false));
}
