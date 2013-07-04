#include "gameengine/coveredbyplayerdecidertest.h"
#include "gameengine/coveredbyplayerdecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

void GameEngine::CoveredByPlayerDeciderTest::decide_defaultField_false()
{
	RouterGridField field;
	RouterGridField previousField;
	CoveredByPlayerDecider decider;

	CPPUNIT_ASSERT(!decider.decide(field, previousField, false));
}

void GameEngine::CoveredByPlayerDeciderTest::decide_playerAtField_true()
{
	RouterGridField field;
	RouterGridField previousField;
	CoveredByPlayerDecider decider;
	field.setPlayer(true);

	CPPUNIT_ASSERT(decider.decide(field, previousField, false));
}
