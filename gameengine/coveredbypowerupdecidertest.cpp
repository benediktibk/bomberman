#include "gameengine/coveredbypowerupdecidertest.h"
#include "gameengine/coveredbypowerupdecider.h"
#include "gameengine/routergridfield.h"

using namespace GameEngine;

void CoveredByPowerUpDeciderTest::decide_defaultField_false()
{
	RouterGridField field;
	CoveredByPowerUpDecider decider;

	CPPUNIT_ASSERT(!decider.decide(field));
}

void CoveredByPowerUpDeciderTest::decide_playerAtField_true()
{
	RouterGridField field;
	CoveredByPowerUpDecider decider;
	field.setPowerUp(true);

	CPPUNIT_ASSERT(decider.decide(field));
}
