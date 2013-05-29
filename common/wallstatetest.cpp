#include "wallstatetest.h"
#include "wallstate.h"
#include "uniqueidcreator.h"

using namespace Common;

void WallStateTest::setPosition_5And4_positionIs5And4()
{
    UniqueIdCreator id;
    WallState wall(id, WallState::WallTypeSolid);

	wall.setPosition(Point(5, 4));

	CPPUNIT_ASSERT_EQUAL(Point(5, 4), wall.getPosition());
}

void WallStateTest::construct_looseWall_typeIsLooseWall()
{
    UniqueIdCreator id;
    WallState wall(id, WallState::WallTypeLoose);

    CPPUNIT_ASSERT_EQUAL(WallState::WallTypeLoose, wall.getWallType());
}

void WallStateTest::construct_solidWall_typeIsSolidWall()
{
    UniqueIdCreator id;
    WallState wall(id, WallState::WallTypeSolid);

    CPPUNIT_ASSERT_EQUAL(WallState::WallTypeSolid, wall.getWallType());
}
