#include "gridtest.h"
#include "grid.h"
#include "common/point.h"
#include "common/bombstate.h"
#include "common/wallstate.h"
#include "common/uniqueidcreator.h"
#include "common/powerupstate.h"
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
    GridPoint point(position);
    CPPUNIT_ASSERT(grid.isPlaceEmpty(point));
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

void GridTest::isPlaceEmpty_withGridPoint()
{
    UniqueIdCreator creator;
    Grid grid(5,5);
    Point position(3.0,3.0);
    WallState wall(creator,WallState::WallTypeLoose,position);
    grid.addWallAtPlace(wall);
    grid.removeWall(wall);
    GridPoint point(position);
    CPPUNIT_ASSERT(grid.isPlaceEmpty(point));
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

	CPPUNIT_ASSERT(count(wallsinrange.begin(), wallsinrange.end(), 0) == 1);
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

	CPPUNIT_ASSERT(count(wallsinrange.begin(), wallsinrange.end(), 1) == 1);
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

	CPPUNIT_ASSERT(count(wallsinrange.begin(), wallsinrange.end(), 2) == 1);
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

	CPPUNIT_ASSERT(count(wallsinrange.begin(), wallsinrange.end(), 3) == 1);
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

	CPPUNIT_ASSERT_EQUAL((size_t)4 , wallsinrange.size());
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

	CPPUNIT_ASSERT_EQUAL((size_t)4 , wallsinrange.size());
}

void GridTest::getWallsInRange_bombat32andwallssurroundingdistance2rangeis2_sizeofwallsinrangeis4()
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

	CPPUNIT_ASSERT_EQUAL((size_t)4 , wallsinrange.size());
}

void GridTest::getWallsInRange_bombat32andwallssurroundingdistance2rangeis1_sizeofwallsinrangeis0()
{
	UniqueIdCreator bombcreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;

	Grid grid(6,7);

	Point position(3.0,2.0);
	BombState bomb(bombcreator);
	bomb.setPosition(position);
	grid.addBombAtPlace(bomb);

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

	CPPUNIT_ASSERT_EQUAL((size_t)0, wallsinrange.size());
}

void GridTest::getWallsInRange_bombat60rangeis1_sizeofwallsinrangeis2()
{
	UniqueIdCreator bombcreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;

	Grid grid(6,7);

	Point position(6.0,0.0);
	BombState bomb(bombcreator);
	bomb.setPosition(position);
	grid.addBombAtPlace(bomb);

	Point position1(5.0,1.0);
	WallState wall1(wallcreator,WallState::WallTypeLoose,position1);
	grid.addWallAtPlace(wall1);

	Point position5(6.0,1.0);
	WallState wall5(wallcreator,WallState::WallTypeLoose,position5);
	grid.addWallAtPlace(wall5);

	Point position6(5.0,0.0);
	WallState wall6(wallcreator,WallState::WallTypeLoose,position6);
	grid.addWallAtPlace(wall6);

	Point position8(1.0,2.0);
	WallState wall8(wallcreator,WallState::WallTypeLoose,position8);
	grid.addWallAtPlace(wall8);

	wallsinrange = grid.getWallsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)2 , wallsinrange.size());
}

void GridTest::getWallsInRange_bombat61rangeis2_sizeofwallsinrangeis3()
{
	UniqueIdCreator bombcreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;

	Grid grid(6,7);

	Point position(6.0,1.0);
	BombState bomb(bombcreator);
	bomb.setPosition(position);
	bomb.setDestructionRange(2);
	grid.addBombAtPlace(bomb);

	Point position1(6.0,0.0);
	WallState wall1(wallcreator,WallState::WallTypeLoose,position1);
	grid.addWallAtPlace(wall1);

	Point position5(5.0,1.0);
	WallState wall5(wallcreator,WallState::WallTypeLoose,position5);
	grid.addWallAtPlace(wall5);

	Point position6(6.0,2.0);
	WallState wall6(wallcreator,WallState::WallTypeLoose,position6);
	grid.addWallAtPlace(wall6);

	Point position8(5.0,0.0);
	WallState wall8(wallcreator,WallState::WallTypeLoose,position8);
	grid.addWallAtPlace(wall8);

	wallsinrange = grid.getWallsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)3, wallsinrange.size());
}

void GridTest::getPowerUpsInRange_bombat33rangeis4BombEmptyWallPowerUp_sizeofwallsinrangeis3()
{
    UniqueIdCreator bombcreator;
    UniqueIdCreator wallcreator;
    UniqueIdCreator powercreator;
    vector<unsigned int> powerUpsInRange;

    Grid grid(7,7);

    Point position(3.0,3.0);
    BombState bomb(bombcreator);
    bomb.setPosition(position);
    bomb.setDestructionRange(4);
    grid.addBombAtPlace(bomb);

    Point position1(5.0,3.0);
    WallState wall1(wallcreator,WallState::WallTypeLoose,position1);
    grid.addWallAtPlace(wall1);

    Point position2(6.0,3.0);
    PowerUpState powerUp(powercreator,position2);
    grid.addPowerUpAtPlace(powerUp);

    powerUpsInRange = grid.getPowerUpsInRange(bomb);

    CPPUNIT_ASSERT_EQUAL((size_t)0, powerUpsInRange.size());
}


void GridTest::getPowerUpsInRange_bombat33rangeis5PowerUpBombPowerUpPowerUpWallPowerUp_sizeofwallsinrangeis3()
{
    UniqueIdCreator bombcreator;
    UniqueIdCreator wallcreator;
    UniqueIdCreator powercreator;
    vector<unsigned int> powerUpsInRange;

    Grid grid(7,7);

    Point position(2.0,3.0);
    BombState bomb(bombcreator);
    bomb.setPosition(position);
    bomb.setDestructionRange(5);
    grid.addBombAtPlace(bomb);

    Point position1(1.0,3.0);
    PowerUpState powerUp(powercreator,position1);
    grid.addPowerUpAtPlace(powerUp);

    Point position2(3.0,3.0);
    PowerUpState powerUp1(powercreator,position2);
    grid.addPowerUpAtPlace(powerUp1);

    Point position3(4.0,3.0);
    PowerUpState powerUp2(powercreator,position3);
    grid.addPowerUpAtPlace(powerUp2);

    Point position4(5.0,3.0);
    WallState wall1(wallcreator,WallState::WallTypeLoose,position4);
    grid.addWallAtPlace(wall1);

    Point position5(6.0,3.0);
    PowerUpState powerUp3(powercreator,position5);
    grid.addPowerUpAtPlace(powerUp3);

    powerUpsInRange = grid.getPowerUpsInRange(bomb);

    CPPUNIT_ASSERT_EQUAL((size_t)3, powerUpsInRange.size());
}

void GridTest::getPowerUpsInRange_bombat59gridsize1010_expectassertionerroringetIndex()
{
    UniqueIdCreator bombcreator;
    vector<unsigned int> wallsInRange;

    Grid grid(10,10);

    Point position(5.0,9.0);
    BombState bomb(bombcreator);
    bomb.setPosition(position);
    bomb.setDestructionRange(5);
    grid.addBombAtPlace(bomb);

       wallsInRange = grid.getWallsInRange(bomb);

    CPPUNIT_ASSERT_EQUAL((size_t)0, wallsInRange.size());
}

void GridTest::isPlaceEmpty_itemat33_false()
{
    UniqueIdCreator wallcreator;

    Grid grid(10,10);

    Point position(3.0,3.0);
    WallState wall1(wallcreator,WallState::WallTypeLoose,position);
    grid.addWallAtPlace(wall1);

    CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::isPlaceEmpty_itemat33_true()
{
    UniqueIdCreator wallcreator;

    Grid grid(10,10);

    Point position(3.0,3.0);
    WallState wall1(wallcreator,WallState::WallTypeLoose,position);
    grid.addWallAtPlace(wall1);
    grid.removeWall(wall1);

    CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}

void GridTest::removePowerUp_itemat33_true()
{
    UniqueIdCreator powerUpCreator;

    Grid grid(10,10);

    Point position(3.0,3.0);
    PowerUpState powerup(powerUpCreator,position);
    grid.addPowerUpAtPlace(powerup);
    grid.removePowerUp(powerup);

    CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}

void GridTest::removeBomb_itemat33_true()
{
    UniqueIdCreator bombCreator;

    Grid grid(10,10);

    Point position(3.0,3.0);
    BombState bomb(bombCreator);
    bomb.setPosition(position);
    grid.addBombAtPlace(bomb);
    grid.removeBomb(bomb);

    CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}

void GridTest::removeWall_itemat33_true()
{
    UniqueIdCreator wallCreator;

    Grid grid(10,10);

    Point position(3.0,3.0);
    WallState wall(wallCreator,WallState::WallTypeLoose,position);
    grid.addWallAtPlace(wall);
    grid.removeWall(wall);

    CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}

void GridTest::getPlayerFields_PlayerAt1comm5and1_11and21()
{
    Grid grid(3,3);
    bool isEqual=false;
    UniqueIdCreator playerCreator;
    PlayerState player(playerCreator);
    vector<GridPoint> gridPoints;
    vector<GridPoint> gridPointsShouldBe;
    Point position(1.5,1.0);
    player.setPosition(position);
    grid.updatePlayer(player);
    gridPoints=grid.getPlayerFields(player);

    GridPoint point1(1,1);
    GridPoint point2(2,1);
    gridPointsShouldBe.push_back(point1);
    gridPointsShouldBe.push_back(point2);
    if(gridPoints==gridPointsShouldBe)
        isEqual=true;

    CPPUNIT_ASSERT(isEqual);
}

void GridTest::getPlayerFields_PlayerAt1and1comma5_11and12()
{
    Grid grid(3,3);
    bool isEqual=false;
    UniqueIdCreator playerCreator;
    PlayerState player(playerCreator);
    vector<GridPoint> gridPoints;
    vector<GridPoint> gridPointsShouldBe;
    Point position(1.0,1.5);
    player.setPosition(position);
    grid.updatePlayer(player);
    gridPoints=grid.getPlayerFields(player);

    GridPoint point1(1,1);
    GridPoint point2(1,2);
    gridPointsShouldBe.push_back(point1);
    gridPointsShouldBe.push_back(point2);
    if(gridPoints==gridPointsShouldBe)
        isEqual=true;

    CPPUNIT_ASSERT(isEqual);
}
