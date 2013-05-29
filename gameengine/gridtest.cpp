#include "gridtest.h"
#include "grid.h"
#include "common/point.h"
#include "common/bombstate.h"
#include "common/wallstate.h"
#include "common/uniqueidcreator.h"

using namespace GameEngine;
using namespace Common;

void GridTest::isPlaceEmpty_TestOnEmptyVector_true()
{
    Grid grid(5.0,5.0);
    Point position(3.0,3.0);
    CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}

void GridTest::isPlaceEmpty_TestNotEmptyVector_false()
{
    UniqueIdCreator creator;
    Grid grid(5.0,5.0);
    Point position(3.0,3.0);
    BombState bomb(creator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);
    CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::addBombAtPlace_add_at3_3()
{
    UniqueIdCreator creator;
    Grid grid(5.0,5.0);
    Point position(3.0,3.0);
    BombState bomb(creator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);
    CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::addWallAtPlace_add_at3_3()
{
    UniqueIdCreator creator;
    Grid grid(5.0,5.0);
    Point position(3.0,3.0);
    WallState wall(creator,WallState::WallTypeLoose,position);
    grid.addWallAtPlace(wall);
    CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::removeBomb_from_3_3()
{
    UniqueIdCreator creator;
    Grid grid(5.0,5.0);
    Point position(3.0,3.0);
    BombState bomb(creator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);
    grid.removeBomb(bomb);
    CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}

void GridTest::removeWall_from_3_3()
{
    UniqueIdCreator creator;
    Grid grid(5.0,5.0);
    Point position(3.0,3.0);
    WallState wall(creator,WallState::WallTypeLoose,position);
    grid.addWallAtPlace(wall);
    grid.removeWall(wall);
    CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}



//void updatePlayer(const Common::PlayerState &player);
