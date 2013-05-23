#include "bombstatetest.h"
#include "bombstate.h"

using namespace Common;

void BombStateTest::setPosition_5And4_positionIs5And4()
{
	BombState bomb;

	bomb.setPosition(Point(5, 4));

	CPPUNIT_ASSERT_EQUAL(Point(5, 4), bomb.getPosition());
}
