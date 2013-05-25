#include "bombstatetest.h"
#include "bombstate.h"

using namespace Common;

void BombStateTest::setPosition_5And4_positionIs5And4()
{
	BombState bomb;

	bomb.setPosition(Point(5, 4));

	CPPUNIT_ASSERT_EQUAL(Point(5, 4), bomb.getPosition());
}

void BombStateTest::setLifeTime_3_lifeTimeIs3()
{
    BombState bomb;

    bomb.setLifeTime(3);

    CPPUNIT_ASSERT_EQUAL(3.0, bomb.getLifeTime());
}
