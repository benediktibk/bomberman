#include "wallstatetest.h"
#include "wallstate.h"

using namespace Common;

void WallStateTest::setPosition_5And4_positionIs5And4()
{
	WallState wall;

	wall.setPosition(Point(5, 4));

	CPPUNIT_ASSERT_EQUAL(Point(5, 4), wall.getPosition());
}
