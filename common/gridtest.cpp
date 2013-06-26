#include "common/gridtest.h"
#include "common/grid.h"
#include "common/gridobservermock.h"
#include "common/point.h"
#include "common/bombstate.h"
#include "common/wallstate.h"
#include "common/uniqueidcreator.h"
#include "common/powerupstate.h"
#include <algorithm>

using namespace Common;
using namespace std;

void GridTest::isPlaceEmpty_TestOnEmptyVector_true()
{
	Grid grid(5, 5);
	Point position(3.0, 3.0);

	CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}

void GridTest::isPlaceEmpty_TestNotEmptyVector_false()
{
	UniqueIdCreator creator;
	Grid grid(5, 5);
	Point position(3, 3);
	BombState bomb(creator, 0, position, 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::addBombAtPlace_add_at3_3()
{
	UniqueIdCreator creator;
	Grid grid(5, 5);
	Point position(3, 3);
	BombState bomb(creator, 0, position, 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::addWallAtPlace_add_at3_3()
{
	UniqueIdCreator creator;
	Grid grid(5, 5);
	Point position(3, 3);
	WallState wall(creator,WallState::WallTypeLoose,position);
	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::removeBomb_from_3_3()
{
	UniqueIdCreator creator;
	Grid grid(5, 5);
	Point position(3, 3);
	BombState bomb(creator, 0, position, 1);
	grid.addBombAtPlace(bomb);
	grid.removeBomb(bomb);
	GridPoint point(position);

	CPPUNIT_ASSERT(grid.isPlaceEmpty(point));
}

void GridTest::removeWall_from_3_3()
{
	UniqueIdCreator creator;
	Grid grid(5, 5);
	Point position(3.0, 3.0);
	WallState wall(creator,WallState::WallTypeLoose,position);
	grid.addWallAtPlace(wall);
	grid.removeWall(wall);

	CPPUNIT_ASSERT(grid.isPlaceEmpty(position));
}

void GridTest::removeWall_addedWall_placeIsEmpty()
{
	UniqueIdCreator creator;
	Grid grid(5, 5);
	Point position(3.0, 3.0);
	WallState wall(creator, WallState::WallTypeLoose, position);
	grid.addWallAtPlace(wall);
	grid.removeWall(wall);
	GridPoint point(position);

	CPPUNIT_ASSERT(grid.isPlaceEmpty(point));
}

void GridTest::isPlaceEmtpy_coveredByNothing_true()
{
	Grid grid(5, 5);

	CPPUNIT_ASSERT(grid.isPlaceEmpty(GridPoint(3, 2)));
}

void GridTest::isPlaceEmpty_coveredByWall_false()
{
	UniqueIdCreator wallIDCreator;
	Grid grid(5, 5);
	Point position(3, 2);
	WallState wall(wallIDCreator, WallState::WallTypeLoose, position);
	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT(!grid.isPlaceEmpty(position));
}

void GridTest::getLooseWallsInRange_bombat32_twowallsup()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;
	Grid grid(6, 7);
	BombState bomb(bombIDCreator, 0, Point(3, 2), 1);
	grid.addBombAtPlace(bomb);
	WallState wall1(wallcreator,WallState::WallTypeLoose, Point(3, 3));
	grid.addWallAtPlace(wall1);
	WallState wall2(wallcreator,WallState::WallTypeLoose, Point(4, 2));
	grid.addWallAtPlace(wall2);

	wallsinrange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT(count(wallsinrange.begin(), wallsinrange.end(), 0) == 1);
}

void GridTest::getLooseWallsInRange_bombat32_twowallsright()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;
	Grid grid(6, 7);
	BombState bomb(bombIDCreator, 0, Point(3, 2), 1);
	grid.addBombAtPlace(bomb);
	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(3, 3));
	grid.addWallAtPlace(wall1);
	WallState wall2(wallcreator, WallState::WallTypeLoose, Point(4, 2));
	grid.addWallAtPlace(wall2);

	wallsinrange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT(count(wallsinrange.begin(), wallsinrange.end(), 1) == 1);
}

void GridTest::getLooseWallsInRange_bombat32_twowallsleft()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;
	Grid grid(6, 7);
	BombState bomb(bombIDCreator, 0, Point(3, 2), 1);
	grid.addBombAtPlace(bomb);
	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(3, 3));
	grid.addWallAtPlace(wall1);
	WallState wall2(wallcreator, WallState::WallTypeLoose, Point(4, 2));
	grid.addWallAtPlace(wall2);
	WallState wall3(wallcreator, WallState::WallTypeLoose, Point(2, 2));
	grid.addWallAtPlace(wall3);
	WallState wall4(wallcreator, WallState::WallTypeLoose, Point(3, 1));
	grid.addWallAtPlace(wall4);

	wallsinrange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT(count(wallsinrange.begin(), wallsinrange.end(), 2) == 1);
}

void GridTest::getLooseWallsInRange_bombat32_twowallsdown()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;
	Grid grid(6, 7);
	BombState bomb(bombIDCreator, 0, Point(3, 2), 1);
	grid.addBombAtPlace(bomb);
	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(3, 3));
	grid.addWallAtPlace(wall1);
	WallState wall2(wallcreator,WallState::WallTypeLoose, Point(4, 2));
	grid.addWallAtPlace(wall2);
	WallState wall3(wallcreator, WallState::WallTypeLoose, Point(2, 2));
	grid.addWallAtPlace(wall3);
	WallState wall4(wallcreator, WallState::WallTypeLoose, Point(3, 1));
	grid.addWallAtPlace(wall4);

	wallsinrange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT(count(wallsinrange.begin(), wallsinrange.end(), 3) == 1);
}

void GridTest::getLooseWallsInRange_bombat32and4wallssurrounding_sizeofwallsinrangeis4()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;
	Grid grid(6, 7);
	BombState bomb(bombIDCreator, 0, Point(3, 2), 1);
	grid.addBombAtPlace(bomb);
	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(3, 3));
	grid.addWallAtPlace(wall1);
	WallState wall2(wallcreator, WallState::WallTypeLoose, Point(4, 2));
	grid.addWallAtPlace(wall2);
	WallState wall3(wallcreator, WallState::WallTypeLoose, Point(2, 2));
	grid.addWallAtPlace(wall3);
	WallState wall4(wallcreator, WallState::WallTypeLoose, Point(3, 1));
	grid.addWallAtPlace(wall4);

	wallsinrange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)4 , wallsinrange.size());
}

void GridTest::getLooseWallsInRange_bombat32and8wallssurroundingrangeis2_sizeofwallsinrangeis4()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;
	Grid grid(6, 7);
	BombState bomb(bombIDCreator, 0, Point(3, 2), 2);
	grid.addBombAtPlace(bomb);
	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(3, 3));
	grid.addWallAtPlace(wall1);
	WallState wall2(wallcreator, WallState::WallTypeLoose, Point(4, 2));
	grid.addWallAtPlace(wall2);
	WallState wall3(wallcreator, WallState::WallTypeLoose, Point(2, 2));
	grid.addWallAtPlace(wall3);
	WallState wall4(wallcreator, WallState::WallTypeLoose, Point(3, 1));
	grid.addWallAtPlace(wall4);
	WallState wall5(wallcreator, WallState::WallTypeLoose, Point(3, 0));
	grid.addWallAtPlace(wall5);
	WallState wall6(wallcreator, WallState::WallTypeLoose, Point(5, 2));
	grid.addWallAtPlace(wall6);
	WallState wall7(wallcreator, WallState::WallTypeLoose, Point(3, 4));
	grid.addWallAtPlace(wall7);
	WallState wall8(wallcreator, WallState::WallTypeLoose, Point(1, 2));
	grid.addWallAtPlace(wall8);

	wallsinrange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)4 , wallsinrange.size());
}

void GridTest::getLooseWallsInRange_bombat32andwallssurroundingdistance2rangeis2_sizeofwallsinrangeis4()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;
	Grid grid(6, 7);
	BombState bomb(bombIDCreator, 0, Point(3, 2), 2);
	grid.addBombAtPlace(bomb);
	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(3, 3));
	grid.addWallAtPlace(wall1);
	WallState wall5(wallcreator, WallState::WallTypeLoose, Point(3, 0));
	grid.addWallAtPlace(wall5);
	WallState wall6(wallcreator, WallState::WallTypeLoose, Point(5, 2));
	grid.addWallAtPlace(wall6);
	WallState wall7(wallcreator, WallState::WallTypeLoose, Point(3, 4));
	grid.addWallAtPlace(wall7);
	WallState wall8(wallcreator,WallState::WallTypeLoose, Point(1, 2));
	grid.addWallAtPlace(wall8);

	wallsinrange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)4 , wallsinrange.size());
}

void GridTest::getLooseWallsInRange_bombat32andwallssurroundingdistance2rangeis1_sizeofwallsinrangeis0()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;
	Grid grid(6, 7);
	BombState bomb(bombIDCreator, 0, Point(3, 2), 1);
	grid.addBombAtPlace(bomb);
	WallState wall5(wallcreator, WallState::WallTypeLoose, Point(3, 0));
	grid.addWallAtPlace(wall5);
	WallState wall6(wallcreator, WallState::WallTypeLoose, Point(5, 2));
	grid.addWallAtPlace(wall6);
	WallState wall7(wallcreator, WallState::WallTypeLoose, Point(3, 4));
	grid.addWallAtPlace(wall7);
	WallState wall8(wallcreator, WallState::WallTypeLoose, Point(1, 2));
	grid.addWallAtPlace(wall8);

	wallsinrange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)0, wallsinrange.size());
}

void GridTest::getLooseWallsInRange_bombat60rangeis1_sizeofwallsinrangeis2()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;
	Grid grid(6, 7);
	BombState bomb(bombIDCreator, 0, Point(6, 0), 1);
	grid.addBombAtPlace(bomb);
	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(5, 1));
	grid.addWallAtPlace(wall1);
	WallState wall5(wallcreator, WallState::WallTypeLoose, Point(6, 1));
	grid.addWallAtPlace(wall5);
	WallState wall6(wallcreator, WallState::WallTypeLoose, Point(5, 0));
	grid.addWallAtPlace(wall6);
	WallState wall8(wallcreator, WallState::WallTypeLoose, Point(1, 2));
	grid.addWallAtPlace(wall8);

	wallsinrange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)2 , wallsinrange.size());
}

void GridTest::getLooseWallsInRange_bombat61rangeis2_sizeofwallsinrangeis3()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	vector<unsigned int> wallsinrange;
	Grid grid(6, 7);
	BombState bomb(bombIDCreator, 0, Point(6, 1), 2);
	grid.addBombAtPlace(bomb);
	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(6, 0));
	grid.addWallAtPlace(wall1);
	WallState wall5(wallcreator, WallState::WallTypeLoose, Point(5, 1));
	grid.addWallAtPlace(wall5);
	WallState wall6(wallcreator, WallState::WallTypeLoose,Point(6, 2));
	grid.addWallAtPlace(wall6);
	WallState wall8(wallcreator, WallState::WallTypeLoose,Point(5, 0));
	grid.addWallAtPlace(wall8);

	wallsinrange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)3, wallsinrange.size());
}

void GridTest::getPowerUpsInRange_bombat33rangeis4BombEmptyWallPowerUp_sizeofwallsinrangeis3()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	UniqueIdCreator powercreator;
	vector<unsigned int> powerUpsInRange;
	Grid grid(7, 7);

	BombState bomb(bombIDCreator, 0, Point(3, 3), 4);
	grid.addBombAtPlace(bomb);
	WallState wall1(wallcreator, WallState::WallTypeLoose,Point(5, 3));
	grid.addWallAtPlace(wall1);
	PowerUpState powerUp(powercreator, Point(6, 3));
	grid.addPowerUpAtPlace(powerUp);

	powerUpsInRange = grid.getPowerUpsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)0, powerUpsInRange.size());
}


void GridTest::getPowerUpsInRange_bombat23RangeIs10PowerUpBombPowerUpPowerUpWallPowerUp_sizeOfPowerUpsInRangeIs3()
{
	UniqueIdCreator bombIDCreator;
	UniqueIdCreator wallcreator;
	UniqueIdCreator powercreator;
	vector<unsigned int> powerUpsInRange;
	Grid grid(7, 7);

	BombState bomb(bombIDCreator, 0, Point(2 ,3), 10);
	grid.addBombAtPlace(bomb);
	PowerUpState powerUp(powercreator, Point(1, 3));
	grid.addPowerUpAtPlace(powerUp);
	PowerUpState powerUp1(powercreator, Point(3, 3));
	grid.addPowerUpAtPlace(powerUp1);
	PowerUpState powerUp2(powercreator, Point(4 ,3));
	grid.addPowerUpAtPlace(powerUp2);
	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(5 ,3));
	grid.addWallAtPlace(wall1);
	PowerUpState powerUp3(powercreator, Point(6 ,3));
	grid.addPowerUpAtPlace(powerUp3);

	powerUpsInRange = grid.getPowerUpsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)3, powerUpsInRange.size());
}

void GridTest::getPowerUpsInRange_bombat59gridsize1010_expectassertionerroringetIndex()
{
	UniqueIdCreator bombIDCreator;
	vector<unsigned int> wallsInRange;
	Grid grid(10, 10);
	BombState bomb(bombIDCreator, 0, Point(5, 9), 5);
	grid.addBombAtPlace(bomb);

	wallsInRange = grid.getLooseWallsInRange(bomb);

	CPPUNIT_ASSERT_EQUAL((size_t)0, wallsInRange.size());
}

void GridTest::getPlayersInRange_playerRightBesideABomb_resultSizeIs1()
{
	UniqueIdCreator playerCreator;
	vector<const PlayerState*> players;
	UniqueIdCreator bombIDCreator;
	Grid grid(10, 10);
	BombState bomb(bombIDCreator, 0, Point(5, 9), 5);
	PlayerState player(playerCreator);
	grid.addBombAtPlace(bomb);
	player.setPosition(Point(5, 8));
	players.push_back(&player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, players);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::isPlaceEmpty_itemat33_false()
{
	UniqueIdCreator wallcreator;
	Grid grid(10, 10);

	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(3, 3));
	grid.addWallAtPlace(wall1);

	CPPUNIT_ASSERT(!grid.isPlaceEmpty(Point(3, 3)));
}

void GridTest::isPlaceEmpty_itemat33_true()
{
	UniqueIdCreator wallcreator;
	Grid grid(10, 10);

	WallState wall1(wallcreator, WallState::WallTypeLoose, Point(3, 3));
	grid.addWallAtPlace(wall1);
	grid.removeWall(wall1);

	CPPUNIT_ASSERT(grid.isPlaceEmpty(Point(3, 3)));
}

void GridTest::removePowerUp_itemat33_true()
{
	UniqueIdCreator powerUpCreator;
	Grid grid(10, 10);

	PowerUpState powerup(powerUpCreator, Point(3, 3));
	grid.addPowerUpAtPlace(powerup);
	grid.removePowerUp(powerup);

	CPPUNIT_ASSERT(grid.isPlaceEmpty(Point(3, 3)));
}

void GridTest::removeBomb_itemat33_true()
{
	UniqueIdCreator bombIDCreator;
	Grid grid(10, 10);

	BombState bomb(bombIDCreator, 0, Point(3, 3), 1);
	grid.addBombAtPlace(bomb);
	grid.removeBomb(bomb);

	CPPUNIT_ASSERT(grid.isPlaceEmpty(Point(3, 3)));
}

void GridTest::removeWall_itemat33_true()
{
	UniqueIdCreator wallCreator;
	Grid grid(10, 10);

	WallState wall(wallCreator, WallState::WallTypeLoose, Point(3.0, 3.0));
	grid.addWallAtPlace(wall);
	grid.removeWall(wall);

	CPPUNIT_ASSERT(grid.isPlaceEmpty(Point(3.0, 3.0)));
}

void GridTest::getPlayerFields_PlayerAt1comm5and1_11and21()
{
	Grid grid(3, 3);
	UniqueIdCreator playerCreator;
	PlayerState player(playerCreator);
	player.setPosition(Point(1.5, 1));

	vector<GridPoint> gridPoints = grid.getPlayerFields(player);

	vector<GridPoint> gridPointsShouldBe;
	gridPointsShouldBe.push_back(GridPoint(1, 1));
	gridPointsShouldBe.push_back(GridPoint(2, 1));

	CPPUNIT_ASSERT(gridPoints == gridPointsShouldBe);
}

void GridTest::getPlayerFields_PlayerAt1and1comma5_11and12()
{
	Grid grid(3, 3);
	UniqueIdCreator playerCreator;
	PlayerState player(playerCreator);
	player.setPosition(Point(1, 1.5));

	vector<GridPoint> gridPoints = grid.getPlayerFields(player);

	vector<GridPoint> gridPointsShouldBe;
	gridPointsShouldBe.push_back(GridPoint(1, 1));
	gridPointsShouldBe.push_back(GridPoint(1, 2));
	CPPUNIT_ASSERT(gridPoints == gridPointsShouldBe);
}

void GridTest::getPlayersInRange_playerWithDifferentXAndYPosition_resultSizeIs0()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 9), 5);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(6, 8));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)0, playersInRange.size());
}

void GridTest::getPlayersInRange_playerAtLeftEndOfDestructionRange_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 2);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(3, 4));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getPlayersInRange_playerAtRightEndOfDestructionRange_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 2);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(7, 4));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getPlayersInRange_playerAtUpperEndOfDestructionRange_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 2);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(5, 6));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getPlayersInRange_playerAtLowerEndOfDestructionRange_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 2);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(5, 2));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getPlayersInRange_playerAfterLeftEndOfDestructionRange_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 2);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(2, 4));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)0, playersInRange.size());
}

void GridTest::getPlayersInRange_playerAfterRightEndOfDestructionRange_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 2);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(8, 4));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)0, playersInRange.size());
}

void GridTest::getPlayersInRange_playerAfterUpperEndOfDestructionRange_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 2);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(5, 7));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)0, playersInRange.size());
}

void GridTest::getPlayersInRange_playerAfterLowerEndOfDestructionRange_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 2);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(5, 1));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)0, playersInRange.size());
}

void GridTest::getPlayersInRange_playerAboveInFrontOfWall_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(5, 8));
	grid.addWallAtPlace(wall);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(5, 7));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getPlayersInRange_playerBelowInFrontOfWall_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(5, 2));
	grid.addWallAtPlace(wall);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(5, 3));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getPlayersInRange_playerLeftInFrontOfWall_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(1, 4));
	grid.addWallAtPlace(wall);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(3, 4));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getPlayersInRange_playerRightInFrontOfWall_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(9, 4));
	grid.addWallAtPlace(wall);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(8, 4));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getPlayersInRange_playerAboveBehindOfLooseWall_resultSizeIs0()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(5, 6));
	grid.addWallAtPlace(wall);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(5, 7));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)0, playersInRange.size());
}

void GridTest::getPlayersInRange_playerBelowBehindOfLooseWall_resultSizeIs0()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(5, 3));
	grid.addWallAtPlace(wall);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(5, 1));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)0, playersInRange.size());
}

void GridTest::getPlayersInRange_playerLeftBehindOfLooseWall_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(3, 4));
	grid.addWallAtPlace(wall);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(2, 4));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)0, playersInRange.size());
}

void GridTest::getPlayersInRange_playerRightBehindOfLooseWall_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 4));
	grid.addWallAtPlace(wall);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(8, 4));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)0, playersInRange.size());
}

void GridTest::getPlayersInRange_playerRightOnTheBomb_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(5, 4));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getPlayersInRange_twoOfTwoPlayersInRange_resultSizeIs2()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	PlayerState* firstPlayer = new PlayerState(*m_playerIdCreator);
	firstPlayer->setPosition(Point(6, 4));
	PlayerState* secondPlayer = new PlayerState(*m_playerIdCreator);
	secondPlayer->setPosition(Point(7, 4));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(firstPlayer);
	allPlayers.push_back(secondPlayer);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)2, playersInRange.size());
}

void GridTest::getPlayersInRange_oneOfTwoPlayersInRange_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	PlayerState* firstPlayer = new PlayerState(*m_playerIdCreator);
	firstPlayer->setPosition(Point(6, 4));
	PlayerState* secondPlayer = new PlayerState(*m_playerIdCreator);
	secondPlayer->setPosition(Point(7, 5));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(firstPlayer);
	allPlayers.push_back(secondPlayer);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getPlayersInRange_playerOnlyHalfInRange_resultSizeIs1()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 4), 5);
	grid.addBombAtPlace(bomb);
	PlayerState* player = new PlayerState(*m_playerIdCreator);
	player->setPosition(Point(7, 4.5));
	std::vector<const PlayerState*> allPlayers;
	allPlayers.push_back(player);

	vector<unsigned int> playersInRange = grid.getPlayersInRange(bomb, allPlayers);

	CPPUNIT_ASSERT_EQUAL((size_t)1, playersInRange.size());
}

void GridTest::getDistanceToNextWallLeft_nothingSet_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, grid.getDistanceToNextWallLeft(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallRight_nothingSet_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);

	CPPUNIT_ASSERT_EQUAL((unsigned int)5, grid.getDistanceToNextWallRight(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallUp_nothingSet_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);

	CPPUNIT_ASSERT_EQUAL((unsigned int)11, grid.getDistanceToNextWallUp(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallDown_nothingSet_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, grid.getDistanceToNextWallDown(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallLeft_wallInRange_distanceIsWayToWall()
{
	Grid grid(15, 10);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(2, 3));
	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, grid.getDistanceToNextWallLeft(Point(4, 3)));
}

void GridTest::getDistanceToNextWallRight_wallInRange_distanceIsWayToWall()
{
	Grid grid(15, 10);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(6, 3));
	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, grid.getDistanceToNextWallRight(Point(4, 3)));
}

void GridTest::getDistanceToNextWallUp_wallInRange_distanceIsWayToWall()
{
	Grid grid(15, 10);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(4, 5));
	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, grid.getDistanceToNextWallUp(Point(4, 3)));
}

void GridTest::getDistanceToNextWallDown_wallInRange_distanceIsWayToWall()
{
	Grid grid(15, 10);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(4, 1));
	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, grid.getDistanceToNextWallDown(Point(4, 3)));
}

void GridTest::getDistanceToNextWallLeft_powerUpInRange_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);
	PowerUpState powerUp(*m_powerUpIdCreator, Point(3, 3));
	grid.addPowerUpAtPlace(powerUp);

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, grid.getDistanceToNextWallLeft(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallRight_powerUpInRange_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);
	PowerUpState powerUp(*m_powerUpIdCreator, Point(5, 3));
	grid.addPowerUpAtPlace(powerUp);

	CPPUNIT_ASSERT_EQUAL((unsigned int)5, grid.getDistanceToNextWallRight(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallUp_powerUpInRange_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);
	PowerUpState powerUp(*m_powerUpIdCreator, Point(4, 4));
	grid.addPowerUpAtPlace(powerUp);

	CPPUNIT_ASSERT_EQUAL((unsigned int)11, grid.getDistanceToNextWallUp(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallDown_powerUpInRange_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);
	PowerUpState powerUp(*m_powerUpIdCreator, Point(4, 2));
	grid.addPowerUpAtPlace(powerUp);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, grid.getDistanceToNextWallDown(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallLeft_bombInRange_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 3), 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, grid.getDistanceToNextWallLeft(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallRight_bombInRange_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(5, 3), 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT_EQUAL((unsigned int)5, grid.getDistanceToNextWallRight(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallUp_bombInRange_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 4), 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT_EQUAL((unsigned int)11, grid.getDistanceToNextWallUp(GridPoint(4, 3)));
}

void GridTest::getDistanceToNextWallDown_bombInRange_distanceIsWayToEndOfLevel()
{
	Grid grid(15, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 2), 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, grid.getDistanceToNextWallDown(GridPoint(4, 3)));
}

void GridTest::constructor_validValues_observerCountIs0()
{
	Grid grid(10, 12);

	CPPUNIT_ASSERT_EQUAL((size_t)0, grid.getObserverCount());
}

void GridTest::addBombAtPlace_oneObserverMock_observerGotCallsToFieldHasChanged()
{
	Grid grid(10, 12);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 1);
	GridObserverMock observer(grid);

	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(observer.getCallsToFieldHasChanged() > 0);
}

void GridTest::addBombAtPlace_bombPosition3And4AndOneObserverMock_observerGotCallToFieldHasChangedWithParam3And4()
{
	Grid grid(10, 12);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 1);
	GridObserverMock observer(grid);

	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(observer.lastParamsOfFieldHasChangedContains(GridPoint(3, 4)));
}

void GridTest::addWallAtPlace_oneObserverMock_observerGotOneCallToFieldHasChanged()
{
	Grid grid(10, 12);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(3, 4));
	GridObserverMock observer(grid);

	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, observer.getCallsToFieldHasChanged());
}

void GridTest::addWallAtPlace_wallPosition3And4AndOneObserverMock_observerGotCallToFieldHasChangedWithParam3And4()
{
	Grid grid(10, 12);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(3, 4));
	GridObserverMock observer(grid);

	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT_EQUAL(GridPoint(3, 4), observer.getLastParamOfCallToFieldHasChanged());
}

void GridTest::removeBomb_bombPosition3And4AndOneObserverMock_observerGotCallsToFieldHasChanged()
{
	Grid grid(10, 12);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 1);
	grid.addBombAtPlace(bomb);
	GridObserverMock observer(grid);

	grid.removeBomb(bomb);

	CPPUNIT_ASSERT(observer.getCallsToFieldHasChanged() > 1);
}

void GridTest::removeBomb_bombPosition3And4AndOneObserverMock_observerGotCallToFieldHasChangedWithParam3And4()
{
	Grid grid(10, 12);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 1);
	grid.addBombAtPlace(bomb);
	GridObserverMock observer(grid);

	grid.removeBomb(bomb);

	CPPUNIT_ASSERT_EQUAL(GridPoint(3, 4), observer.getLastParamOfCallToFieldHasChanged());
}

void GridTest::removeWall_oneObserverMock_observerGotOneCallToFieldHasChanged()
{
	Grid grid(10, 12);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(3, 4));
	grid.addWallAtPlace(wall);
	GridObserverMock observer(grid);

	grid.removeWall(wall);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, observer.getCallsToFieldHasChanged());
}

void GridTest::removeWall_wallPosition1And0AndOneObserverMock_observerGotCallToFieldHasChangedWithParam1And0()
{
	Grid grid(10, 12);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(3, 4));
	grid.addWallAtPlace(wall);
	GridObserverMock observer(grid);

	grid.removeWall(wall);

	CPPUNIT_ASSERT_EQUAL(GridPoint(3, 4), observer.getLastParamOfCallToFieldHasChanged());
}

void GridTest::removeWall_wallAddedPreviouslyAndOneObserverMock_observerGotTwoCallsToFieldHasChanged()
{
	Grid grid(10, 12);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(3, 4));
	GridObserverMock observer(grid);
	grid.addWallAtPlace(wall);

	grid.removeWall(wall);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, observer.getCallsToFieldHasChanged());
}

void GridTest::isPlaceCoveredBySolidWall_coveredByLooseWall_false()
{
	Grid grid(15, 13);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(1, 6));
	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT(!grid.isPlaceCoveredBySolidWall(GridPoint(1, 6)));
}

void GridTest::isPlaceCoveredBySolidWall_coveredBySolidWall_true()
{
	Grid grid(15, 13);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(1, 6));
	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT(grid.isPlaceCoveredBySolidWall(GridPoint(1, 6)));
}

void GridTest::isPlaceCoveredByLooseWall_coveredByLooseWall_true()
{
	Grid grid(15, 13);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(1, 6));
	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT(grid.isPlaceCoveredByLooseWall(GridPoint(1, 6)));
}

void GridTest::isPlaceCoveredByLooseWall_coveredBySolidWall_false()
{
	Grid grid(15, 13);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(1, 6));
	grid.addWallAtPlace(wall);

	CPPUNIT_ASSERT(!grid.isPlaceCoveredByLooseWall(GridPoint(1, 6)));
}

void GridTest::isPlaceCoveredByBomb_free_false()
{
	Grid grid(15, 13);

	CPPUNIT_ASSERT(!grid.isPlaceCoveredByBomb(GridPoint(12, 11)));
}

void GridTest::isPlaceCoveredByBomb_coveredByBomb_true()
{
	Grid grid(15, 13);
	BombState bomb(*m_bombIdCreator, 0, Point(12, 11), 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(grid.isPlaceCoveredByBomb(GridPoint(12, 11)));
}

void GridTest::getTargetPoint_onlyField5And6Covered_5And6()
{
	PlayerState player(*m_playerIdCreator);
	player.setPosition(Point(5, 6));

	CPPUNIT_ASSERT_EQUAL(GridPoint(5, 6), Grid::getTargetPoint(player));
}

void GridTest::getTargetPoint_between5And6And6And6AndMovingRight_6And6()
{
	PlayerState player(*m_playerIdCreator);
	player.setPosition(Point(5.5, 6));
	player.setDirectionRight();

	CPPUNIT_ASSERT_EQUAL(GridPoint(6, 6), Grid::getTargetPoint(player));
}

void GridTest::getTargetPoint_between5And6And6And6AndMovingLeft_5And6()
{
	PlayerState player(*m_playerIdCreator);
	player.setPosition(Point(5.5, 6));
	player.setDirectionLeft();

	CPPUNIT_ASSERT_EQUAL(GridPoint(5, 6), Grid::getTargetPoint(player));
}

void GridTest::getTargetPoint_between5And6And5And7AndMovingUp_5And7()
{
	PlayerState player(*m_playerIdCreator);
	player.setPosition(Point(5, 6.5));
	player.setDirectionUp();

	CPPUNIT_ASSERT_EQUAL(GridPoint(5, 7), Grid::getTargetPoint(player));
}

void GridTest::getTargetPoint_between5And6And5And7AndMovingDown_5And6()
{
	PlayerState player(*m_playerIdCreator);
	player.setPosition(Point(5, 6.5));
	player.setDirectionDown();

	CPPUNIT_ASSERT_EQUAL(GridPoint(5, 6), Grid::getTargetPoint(player));
}

void GridTest::isPlaceDangerous_noBombs_false()
{
	Grid grid(10, 10);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(4, 3)));
}

void GridTest::isPlaceDangerous_rightOnBomb_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(4, 3)));
}

void GridTest::isPlaceDangerous_oneLeftOfBomb_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(3, 3)));
}

void GridTest::isPlaceDangerous_oneRightOfBomb_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(5, 3)));
}

void GridTest::isPlaceDangerous_oneAboveOfBomb_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(4, 4)));
}

void GridTest::isPlaceDangerous_oneBelowOfBomb_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 1);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(4, 2)));
}

void GridTest::isPlaceDangerous_twoRightOfBombWithRangeTwo_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 2);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(6, 3)));
}

void GridTest::isPlaceDangerous_twoLeftOfBombWithRangeTwo_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 2);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(2, 3)));
}

void GridTest::isPlaceDangerous_twoAboveOfBombWithRangeTwo_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 2);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(4, 5)));
}

void GridTest::isPlaceDangerous_twoBelowOfBombWithRangeTwo_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 2);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(4, 1)));
}

void GridTest::isPlaceDangerous_threeRightOfBombWithRangeTwo_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 2);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(7, 3)));
}

void GridTest::isPlaceDangerous_threeLeftOfBombWithRangeTwo_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 2);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(1, 3)));
}

void GridTest::isPlaceDangerous_threeAboveOfBombWithRangeTwo_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 2);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(4, 6)));
}

void GridTest::isPlaceDangerous_threeBelowOfBombWithRangeTwo_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 2);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(4, 0)));
}

void GridTest::isPlaceDangerous_positionRightOfBombBehindLooseWall_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(6, 3));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(7, 3)));
}

void GridTest::isPlaceDangerous_positionLeftOfBombBehindLooseWall_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(2, 3));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(0, 3)));
}

void GridTest::isPlaceDangerous_positionAboveOfBombBehindLooseWall_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(4, 4));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(4, 8)));
}

void GridTest::isPlaceDangerous_positionBelowOfBombBehindLooseWall_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(4, 1));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(4, 0)));
}

void GridTest::isPlaceDangerous_positionRightOfBombBehindSolidWall_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(6, 3));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(7, 3)));
}

void GridTest::isPlaceDangerous_positionLeftOfBombBehindSolidWall_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(2, 3));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(0, 3)));
}

void GridTest::isPlaceDangerous_positionAboveOfBombBehindSolidWall_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(4, 4));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(4, 8)));
}

void GridTest::isPlaceDangerous_positionBelowOfBombBehindSolidWall_false()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(4, 1));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(4, 0)));
}

void GridTest::isPlaceDangerous_positionRightOfBombBehindRemovedLooseWall_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(6, 3));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);
	grid.removeWall(wall);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(7, 3)));
}

void GridTest::isPlaceDangerous_positionLeftOfBombBehindRemovedLooseWall_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(2, 3));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);
	grid.removeWall(wall);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(0, 3)));
}

void GridTest::isPlaceDangerous_positionAboveOfBombBehindRemovedLooseWall_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(4, 4));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);
	grid.removeWall(wall);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(4, 8)));
}

void GridTest::isPlaceDangerous_positionBelowOfBombBehindRemovedLooseWall_true()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(4, 3), 100);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(4, 1));
	grid.addWallAtPlace(wall);
	grid.addBombAtPlace(bomb);
	grid.removeWall(wall);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(4, 0)));
}

void GridTest::isPlaceDangerous_inRangeOfTwoBombsButOneRemoved_true()
{
	Grid grid(10, 10);
	BombState bombOne(*m_bombIdCreator, 0, Point(7, 4), 100);
	BombState bombTwo(*m_bombIdCreator, 0, Point(2, 0), 100);
	grid.addBombAtPlace(bombOne);
	grid.addBombAtPlace(bombTwo);
	grid.removeBomb(bombOne);

	CPPUNIT_ASSERT(grid.isPlaceDangerous(GridPoint(2, 4)));
}

void GridTest::isPlaceDangerous_inRangeOfTwoRemovedBombs_false()
{
	Grid grid(10, 10);
	BombState bombOne(*m_bombIdCreator, 0, Point(7, 4), 100);
	BombState bombTwo(*m_bombIdCreator, 0, Point(2, 0), 100);
	grid.addBombAtPlace(bombOne);
	grid.addBombAtPlace(bombTwo);
	grid.removeBomb(bombOne);
	grid.removeBomb(bombTwo);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(2, 4)));
}

void GridTest::removeBomb_bombWithRange2AndOneObserverMock_observerGotCallToFieldHasChangedTwoFieldsRightOfBombPosition()
{
	Grid grid(10, 10);
	GridObserverMock observer(grid);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 2);
	grid.addBombAtPlace(bomb);
	observer.clearLastParamsOfFieldHasChanged();

	grid.removeBomb(bomb);

	CPPUNIT_ASSERT(observer.lastParamsOfFieldHasChangedContains(GridPoint(5, 4)));
}

void GridTest::removeBomb_bombWithRange2AndOneObserverMock_observerGotCallToFieldHasChangedTwoFieldsAboveOfBombPosition()
{
	Grid grid(10, 10);
	GridObserverMock observer(grid);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 2);
	grid.addBombAtPlace(bomb);
	observer.clearLastParamsOfFieldHasChanged();

	grid.removeBomb(bomb);

	CPPUNIT_ASSERT(observer.lastParamsOfFieldHasChangedContains(GridPoint(3, 6)));
}

void GridTest::removeWall_wallLeftOfBombInRangeOfBombAndOneObserverMock_observerGotCallToFieldHasChangedBehindTheWall()
{
	Grid grid(10, 10);
	GridObserverMock observer(grid);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 2);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(2, 4));
	grid.addBombAtPlace(bomb);
	grid.addWallAtPlace(wall);
	observer.clearLastParamsOfFieldHasChanged();

	grid.removeWall(wall);

	CPPUNIT_ASSERT(observer.lastParamsOfFieldHasChangedContains(GridPoint(1, 4)));
}

void GridTest::removeWall_wallBelowOfBombInRangeOfBombAndOneObserverMock_observerGotCallToFieldHasChangedBehindTheWall()
{
	Grid grid(10, 10);
	GridObserverMock observer(grid);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 4);
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(3, 2));
	grid.addBombAtPlace(bomb);
	grid.addWallAtPlace(wall);
	observer.clearLastParamsOfFieldHasChanged();

	grid.removeWall(wall);

	CPPUNIT_ASSERT(observer.lastParamsOfFieldHasChangedContains(GridPoint(3, 1)));
}

void GridTest::addBombAtPlace_bombWithRange2AndOneObserverMock_observerGotCallToFieldHasChangedOneFieldLeftOfBombPosition()
{
	Grid grid(10, 10);
	GridObserverMock observer(grid);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 2);

	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(observer.lastParamsOfFieldHasChangedContains(GridPoint(2, 4)));
}

void GridTest::addBombAtPlace_bombWithRange2AndOneObserverMock_observerGotCallToFieldHasChangedOneFieldAboveOfBombPosition()
{
	Grid grid(10, 10);
	GridObserverMock observer(grid);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 2);

	grid.addBombAtPlace(bomb);

	CPPUNIT_ASSERT(observer.lastParamsOfFieldHasChangedContains(GridPoint(3, 5)));
}

void GridTest::removeBomb_bombWithRange1AtPosition3And4_3And4IsNotDangerous()
{
	Grid grid(10, 10);
	BombState bomb(*m_bombIdCreator, 0, Point(3, 4), 1);
	grid.addBombAtPlace(bomb);

	grid.removeBomb(bomb);

	CPPUNIT_ASSERT(!grid.isPlaceDangerous(GridPoint(3, 4)));
}

void GridTest::setUp()
{
	m_powerUpIdCreator = new UniqueIdCreator();
	m_wallIdCreator = new UniqueIdCreator();
	m_bombIdCreator = new UniqueIdCreator();
	m_playerIdCreator = new UniqueIdCreator();
}

void GridTest::tearDown()
{
	delete m_powerUpIdCreator;
	m_powerUpIdCreator = 0;
	delete m_wallIdCreator;
	m_wallIdCreator = 0;
	delete m_bombIdCreator;
	m_bombIdCreator = 0;
	delete m_playerIdCreator;
	m_playerIdCreator = 0;
}
