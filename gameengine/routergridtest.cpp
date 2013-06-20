#include "gameengine/routergridtest.h"
#include "gameengine/routergrid.h"
#include "gameengine/grid.h"
#include "common/gamestate.h"
#include "common/bombstate.h"
#include "common/wallstate.h"
#include "common/powerupstate.h"
#include "common/uniqueidcreator.h"

using namespace GameEngine;
using namespace Common;

void RouterGridTest::setUp()
{
	m_bombIdCreator = new UniqueIdCreator();
	m_wallIdCreator = new UniqueIdCreator();
	m_powerUpIdCreator = new UniqueIdCreator();
	m_playerIdCreator = new UniqueIdCreator();
	LevelDefinition level(10, 15);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	m_grid = new Grid(level.getLevelHeight(), level.getLevelWidth());
	m_gameState = new GameState(level, 1, *m_playerIdCreator, *m_wallIdCreator);
}

void RouterGridTest::tearDown()
{
	delete m_gameState;
	m_gameState = 0;
	delete m_grid;
	m_grid = 0;
	delete m_bombIdCreator;
	m_bombIdCreator = 0;
	delete m_wallIdCreator;
	m_wallIdCreator = 0;
	delete m_powerUpIdCreator;
	m_powerUpIdCreator = 0;
	delete m_playerIdCreator;
	m_playerIdCreator = 0;
}

void RouterGridTest::constructor_gridWith15RowsAnd10Columns_widthIs10()
{
	RouterGrid routerGrid(*m_grid, *m_gameState);

	CPPUNIT_ASSERT_EQUAL((unsigned int)10, routerGrid.getWidth());
}

void RouterGridTest::constructor_gridWith15RowsAnd10Columns_heightIs15()
{
	RouterGrid routerGrid(*m_grid, *m_gameState);

	CPPUNIT_ASSERT_EQUAL((unsigned int)15, routerGrid.getHeight());
}

void RouterGridTest::constructor_bombAt3And5InGrid_bombAt3And5()
{
	BombState bomb(*m_bombIdCreator, 0);
	bomb.setPosition(Point(3, 5));
	m_grid->addBombAtPlace(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 5));
	CPPUNIT_ASSERT(gridField.isBomb());
}

void RouterGridTest::constructor_bombAt3And5InGrid_noSolidWallAt3And5()
{
	BombState bomb(*m_bombIdCreator, 0);
	bomb.setPosition(Point(3, 5));
	m_grid->addBombAtPlace(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 5));
	CPPUNIT_ASSERT(!gridField.isSolidWall());
}

void RouterGridTest::constructor_bombAt3And5InGrid_noLooseWallAt3And5()
{
	BombState bomb(*m_bombIdCreator, 0);
	bomb.setPosition(Point(3, 5));
	m_grid->addBombAtPlace(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 5));
	CPPUNIT_ASSERT(!gridField.isLooseWall());
}

void RouterGridTest::constructor_bombAt3And5InGrid_dangerousAt3And5()
{
	BombState bomb(*m_bombIdCreator, 0);
	bomb.setPosition(Point(3, 5));
	m_grid->addBombAtPlace(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 5));
	CPPUNIT_ASSERT(gridField.isDangerous());
}

void RouterGridTest::constructor_bombAt3And5InGrid_noPlayerAt3And5()
{
	BombState bomb(*m_bombIdCreator, 0);
	bomb.setPosition(Point(3, 5));
	m_grid->addBombAtPlace(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 5));
	CPPUNIT_ASSERT(!gridField.isPlayer());
}

void RouterGridTest::constructor_looseWallAt7And5InGrid_looseWallAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(gridField.isLooseWall());
}

void RouterGridTest::constructor_looseWallAt7And5InGrid_noSolidWallAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isSolidWall());
}

void RouterGridTest::constructor_looseWallAt7And5InGrid_noBombAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isBomb());
}

void RouterGridTest::constructor_looseWallAt7And5InGrid_notDangerousAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_looseWallAt7And5InGrid_noPlayerAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isPlayer());
}

void RouterGridTest::constructor_solidWallAt7And5InGrid_noLooseWallAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isLooseWall());
}

void RouterGridTest::constructor_solidWallAt7And5InGrid_solidWallAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(gridField.isSolidWall());
}

void RouterGridTest::constructor_solidWallAt7And5InGrid_noBombAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isBomb());
}

void RouterGridTest::constructor_solidWallAt7And5InGrid_notDangerousAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_solidWallAt7And5InGrid_noPlayerAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isPlayer());
}

void RouterGridTest::constructor_powerUpAt8And9InGrid_noSolidWallAt8And9()
{
	PowerUpState powerUp(*m_powerUpIdCreator, Point(8, 9));
	m_grid->addPowerUpAtPlace(powerUp);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 9));
	CPPUNIT_ASSERT(!gridField.isSolidWall());
}

void RouterGridTest::constructor_powerUpAt8And9InGrid_noLooseWallAt8And9()
{
	PowerUpState powerUp(*m_powerUpIdCreator, Point(8, 9));
	m_grid->addPowerUpAtPlace(powerUp);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 9));
	CPPUNIT_ASSERT(!gridField.isLooseWall());
}

void RouterGridTest::constructor_powerUpAt8And9InGrid_noPlayerAt8And9()
{
	PowerUpState powerUp(*m_powerUpIdCreator, Point(8, 9));
	m_grid->addPowerUpAtPlace(powerUp);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 9));
	CPPUNIT_ASSERT(!gridField.isPlayer());
}

void RouterGridTest::constructor_powerUpAt8And9InGrid_noBombAt8And9()
{
	PowerUpState powerUp(*m_powerUpIdCreator, Point(8, 9));
	m_grid->addPowerUpAtPlace(powerUp);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 9));
	CPPUNIT_ASSERT(!gridField.isBomb());
}

void RouterGridTest::constructor_powerUpAt8And9InGrid_notDangerousAt8And9()
{
	PowerUpState powerUp(*m_powerUpIdCreator, Point(8, 9));
	m_grid->addPowerUpAtPlace(powerUp);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 9));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange2At5And4_7And4IsDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(2);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 4));
	CPPUNIT_ASSERT(gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange2At5And4_8And4IsNotDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(2);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 4));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange10At5And4AndWallAt6And4_7And4IsNotDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(10);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(6, 4));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 4));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange2At5And4_3And4IsDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(2);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 4));
	CPPUNIT_ASSERT(gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange2At5And4_2And4IsNotDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(2);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(2, 4));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange10At5And4AndWallAt4And4_3And4IsNotDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(10);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(4, 4));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 4));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange2At5And4_5And6IsDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(2);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(5, 6));
	CPPUNIT_ASSERT(gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange2At5And4_5And7IsNotDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(2);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(5, 7));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange10At5And4AndWallAt5And5_5And6IsNotDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(10);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(5, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(5, 6));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange2At5And4_5And2IsDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(2);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(5, 2));
	CPPUNIT_ASSERT(gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange2At5And4_5And1IsNotDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(2);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(5, 1));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_bombWithRange10At5And4AndWallAt5And3_5And2IsNotDangerous()
{
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(5, 4));
	bomb->setDestructionRange(10);
	m_grid->addBombAtPlace(*bomb);
	m_gameState->addBomb(bomb);
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(5, 3));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid, *m_gameState);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(5, 2));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}
