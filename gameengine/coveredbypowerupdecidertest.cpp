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

void CoveredByPowerUpDeciderTest::decide_powerUpAtField_true()
{
	RouterGridField field;
	CoveredByPowerUpDecider decider;
	field.setPowerUp(true);

	CPPUNIT_ASSERT(decider.decide(field));
}

void CoveredByPowerUpDeciderTest::decide_powerUpAtFieldAndDangerous_false()
{
	RouterGridField field;
	CoveredByPowerUpDecider decider;
	field.setPowerUp(true);
	field.setDangerous(true);

	CPPUNIT_ASSERT(!decider.decide(field));
}
