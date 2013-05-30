#include "gridtest.h"
#include "grid.h"
#include "common/point.h"
#include "common/bombstate.h"
#include "common/wallstate.h"
#include "common/uniqueidcreator.h"
#include <algorithm>

using namespace GameEngine;
using namespace Common;
using namespace std;

void GridTest::isPlaceEmpty_TestOnEmptyVector_true()
{
    Grid grid(5,5);
    Point position(3.0,3.0);
    CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}

void GridTest::isPlaceEmpty_TestNotEmptyVector_false()
{
    UniqueIdCreator creator;
    Grid grid(5,5);
    Point position(3.0,3.0);
    BombState bomb(creator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);
    CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::addBombAtPlace_add_at3_3()
{
    UniqueIdCreator creator;
    Grid grid(5,5);
    Point position(3.0,3.0);
    BombState bomb(creator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);
    CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::addWallAtPlace_add_at3_3()
{
    UniqueIdCreator creator;
    Grid grid(5,5);
    Point position(3.0,3.0);
    WallState wall(creator,WallState::WallTypeLoose,position);
    grid.addWallAtPlace(wall);
    CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::removeBomb_from_3_3()
{
    UniqueIdCreator creator;
    Grid grid(5,5);
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
    Grid grid(5,5);
    Point position(3.0,3.0);
    WallState wall(creator,WallState::WallTypeLoose,position);
    grid.addWallAtPlace(wall);
    grid.removeWall(wall);
    CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}

void GridTest::getWallsInRange_bombat32_twowallsup()
{
    UniqueIdCreator bombcreator;
    UniqueIdCreator wallcreator;
    vector<unsigned int> wallsinrange;

    Grid grid(6,7);

    Point position(3.0,2.0);
    BombState bomb(bombcreator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);

    Point position1(3.0,3.0);
    WallState wall1(wallcreator,WallState::WallTypeLoose,position1);
    grid.addWallAtPlace(wall1);

    Point position2(4.0,2.0);
    WallState wall2(wallcreator,WallState::WallTypeLoose,position2);
    grid.addWallAtPlace(wall2);

    wallsinrange = grid.getWallsInRange(bomb);

    CPPUNIT_ASSERT_EQUAL((int)1, count(wallsinrange.begin(), wallsinrange.end(), 0));
}

void GridTest::getWallsInRange_bombat32_twowallsright()
{
    UniqueIdCreator bombcreator;
    UniqueIdCreator wallcreator;
    vector<unsigned int> wallsinrange;

    Grid grid(6,7);

    Point position(3.0,2.0);
    BombState bomb(bombcreator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);

    Point position1(3.0,3.0);
    WallState wall1(wallcreator,WallState::WallTypeLoose,position1);
    grid.addWallAtPlace(wall1);

    Point position2(4.0,2.0);
    WallState wall2(wallcreator,WallState::WallTypeLoose,position2);
    grid.addWallAtPlace(wall2);

    wallsinrange = grid.getWallsInRange(bomb);


    CPPUNIT_ASSERT_EQUAL((int)1, count(wallsinrange.begin(), wallsinrange.end(), 1));
}


void GridTest::getWallsInRange_bombat32_twowallsleft()
{
    UniqueIdCreator bombcreator;
    UniqueIdCreator wallcreator;
    vector<unsigned int> wallsinrange;

    Grid grid(6,7);

    Point position(3.0,2.0);
    BombState bomb(bombcreator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);

    Point position1(3.0,3.0);
    WallState wall1(wallcreator,WallState::WallTypeLoose,position1);
    grid.addWallAtPlace(wall1);

    Point position2(4.0,2.0);
    WallState wall2(wallcreator,WallState::WallTypeLoose,position2);
    grid.addWallAtPlace(wall2);

    Point position3(2.0,2.0);
    WallState wall3(wallcreator,WallState::WallTypeLoose,position3);
    grid.addWallAtPlace(wall3);

    Point position4(3.0,1.0);
    WallState wall4(wallcreator,WallState::WallTypeLoose,position4);
    grid.addWallAtPlace(wall4);

    wallsinrange = grid.getWallsInRange(bomb);


    CPPUNIT_ASSERT_EQUAL((int)1, count(wallsinrange.begin(), wallsinrange.end(), 2));
}

void GridTest::getWallsInRange_bombat32_twowallsdown()
{
    UniqueIdCreator bombcreator;
    UniqueIdCreator wallcreator;
    vector<unsigned int> wallsinrange;


    Grid grid(6,7);

    Point position(3.0,2.0);
    BombState bomb(bombcreator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);

    Point position1(3.0,3.0);
    WallState wall1(wallcreator,WallState::WallTypeLoose,position1);
    grid.addWallAtPlace(wall1);

    Point position2(4.0,2.0);
    WallState wall2(wallcreator,WallState::WallTypeLoose,position2);
    grid.addWallAtPlace(wall2);

    Point position3(2.0,2.0);
    WallState wall3(wallcreator,WallState::WallTypeLoose,position3);
    grid.addWallAtPlace(wall3);

    Point position4(3.0,1.0);
    WallState wall4(wallcreator,WallState::WallTypeLoose,position4);
    grid.addWallAtPlace(wall4);

    wallsinrange = grid.getWallsInRange(bomb);


    CPPUNIT_ASSERT_EQUAL((int)1, count(wallsinrange.begin(), wallsinrange.end(), 3));
}

void GridTest::getWallsInRange_bombat32and4wallssurrounding_sizeofwallsinrangeis4()
{
    UniqueIdCreator bombcreator;
    UniqueIdCreator wallcreator;
    vector<unsigned int> wallsinrange;

    Grid grid(6,7);

    Point position(3.0,2.0);
    BombState bomb(bombcreator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);

    Point position1(3.0,3.0);
    WallState wall1(wallcreator,WallState::WallTypeLoose,position1);
    grid.addWallAtPlace(wall1);

    Point position2(4.0,2.0);
    WallState wall2(wallcreator,WallState::WallTypeLoose,position2);
    grid.addWallAtPlace(wall2);

    Point position3(2.0,2.0);
    WallState wall3(wallcreator,WallState::WallTypeLoose,position3);
    grid.addWallAtPlace(wall3);

    Point position4(3.0,1.0);
    WallState wall4(wallcreator,WallState::WallTypeLoose,position4);
    grid.addWallAtPlace(wall4);

    wallsinrange = grid.getWallsInRange(bomb);


    CPPUNIT_ASSERT_EQUAL((unsigned int)4 , wallsinrange.size());
}




void GridTest::getWallsInRange_bombat32and8wallssurroundingrangeis2_sizeofwallsinrangeis4()
{
    UniqueIdCreator bombcreator;
    UniqueIdCreator wallcreator;
    vector<unsigned int> wallsinrange;

    Grid grid(6,7);

    Point position(3.0,2.0);
    BombState bomb(bombcreator);
    bomb.setPosition(position);
    bomb.setDestructionRange(2);
    grid.addBombAtPlace(bomb);

    Point position1(3.0,3.0);
    WallState wall1(wallcreator,WallState::WallTypeLoose,position1);
    grid.addWallAtPlace(wall1);

    Point position2(4.0,2.0);
    WallState wall2(wallcreator,WallState::WallTypeLoose,position2);
    grid.addWallAtPlace(wall2);

    Point position3(2.0,2.0);
    WallState wall3(wallcreator,WallState::WallTypeLoose,position3);
    grid.addWallAtPlace(wall3);

    Point position4(3.0,1.0);
    WallState wall4(wallcreator,WallState::WallTypeLoose,position4);
    grid.addWallAtPlace(wall4);

    Point position5(3.0,0.0);
    WallState wall5(wallcreator,WallState::WallTypeLoose,position5);
    grid.addWallAtPlace(wall5);

    Point position6(5.0,2.0);
    WallState wall6(wallcreator,WallState::WallTypeLoose,position6);
    grid.addWallAtPlace(wall6);

    Point position7(3.0,4.0);
    WallState wall7(wallcreator,WallState::WallTypeLoose,position7);
    grid.addWallAtPlace(wall7);

    Point position8(1.0,2.0);
    WallState wall8(wallcreator,WallState::WallTypeLoose,position8);
    grid.addWallAtPlace(wall8);

    wallsinrange = grid.getWallsInRange(bomb);


    CPPUNIT_ASSERT_EQUAL((unsigned int)4 , wallsinrange.size());
}

//void updatePlayer(const Common::PlayerState &player);
