#include "wallstatetest.h"
#include "wallstate.h"
#include "uniqueidcreator.h"

using namespace Common;

void WallStateTest::construct_looseWall_typeIsLooseWall()
{
	UniqueIdCreator id;
	WallState wall(id, WallState::WallTypeLoose, Point());

	CPPUNIT_ASSERT_EQUAL(WallState::WallTypeLoose, wall.getWallType());
}

void WallStateTest::setDestroyed_empty_hasChanged()
{
	UniqueIdCreator id;
	WallState wall(id, WallState::WallTypeLoose, Point());

	wall.setDestroyed();

	CPPUNIT_ASSERT(wall.hasChanged());
}

void WallStateTest::construct_solidWall_typeIsSolidWall()
{
	UniqueIdCreator id;
	WallState wall(id, WallState::WallTypeSolid, Point());

	CPPUNIT_ASSERT_EQUAL(WallState::WallTypeSolid, wall.getWallType());
}

void WallStateTest::getWallHeight_heightIs1()
{
    UniqueIdCreator id;
    WallState wall(id, WallState::WallTypeLoose, Point());

    CPPUNIT_ASSERT_EQUAL(1.0, wall.getHeight());
}

void WallStateTest::getWallWidth_widthIs1()
{
    UniqueIdCreator id;
    WallState wall(id, WallState::WallTypeLoose, Point());

    CPPUNIT_ASSERT_EQUAL(1.0, wall.getWidth());
}
