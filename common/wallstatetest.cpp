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

void WallStateTest::construct_solidWall_typeIsSolidWall()
{
	UniqueIdCreator id;
	WallState wall(id, WallState::WallTypeSolid, Point());

	CPPUNIT_ASSERT_EQUAL(WallState::WallTypeSolid, wall.getWallType());
}