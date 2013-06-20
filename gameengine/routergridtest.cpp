#include "gameengine/routergridtest.h"
#include "gameengine/routergrid.h"
#include "gameengine/grid.h"
#include "common/bombstate.h"
#include "common/wallstate.h"
#include "common/powerupstate.h"
#include "common/uniqueidcreator.h"

using namespace GameEngine;
using namespace Common;

void RouterGridTest::setUp()
{
	m_grid = new Grid(15, 10);
	m_bombIdCreator = new UniqueIdCreator();
	m_wallIdCreator = new UniqueIdCreator();
	m_powerUpIdCreator = new UniqueIdCreator();
}

void RouterGridTest::tearDown()
{
	delete m_grid;
	m_grid = 0;
	delete m_bombIdCreator;
	m_bombIdCreator = 0;
	delete m_wallIdCreator;
	m_wallIdCreator = 0;
	delete m_powerUpIdCreator;
	m_powerUpIdCreator = 0;
}

void RouterGridTest::constructor_gridWith15RowsAnd10Columns_widthIs10()
{
	RouterGrid routerGrid(*m_grid);

	CPPUNIT_ASSERT_EQUAL((unsigned int)10, routerGrid.getWidth());
}

void RouterGridTest::constructor_gridWith15RowsAnd10Columns_heightIs15()
{
	RouterGrid routerGrid(*m_grid);

	CPPUNIT_ASSERT_EQUAL((unsigned int)15, routerGrid.getHeight());
}

void RouterGridTest::constructor_bombAt3And5InGrid_bombAt3And5()
{
	BombState bomb(*m_bombIdCreator, 0);
	bomb.setPosition(Point(3, 5));
	m_grid->addBombAtPlace(bomb);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 5));
	CPPUNIT_ASSERT(gridField.isBomb());
}

void RouterGridTest::constructor_bombAt3And5InGrid_noSolidWallAt3And5()
{
	BombState bomb(*m_bombIdCreator, 0);
	bomb.setPosition(Point(3, 5));
	m_grid->addBombAtPlace(bomb);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 5));
	CPPUNIT_ASSERT(!gridField.isSolidWall());
}

void RouterGridTest::constructor_bombAt3And5InGrid_noLooseWallAt3And5()
{
	BombState bomb(*m_bombIdCreator, 0);
	bomb.setPosition(Point(3, 5));
	m_grid->addBombAtPlace(bomb);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 5));
	CPPUNIT_ASSERT(!gridField.isLooseWall());
}

void RouterGridTest::constructor_bombAt3And5InGrid_dangerousAt3And5()
{
	BombState bomb(*m_bombIdCreator, 0);
	bomb.setPosition(Point(3, 5));
	m_grid->addBombAtPlace(bomb);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 5));
	CPPUNIT_ASSERT(gridField.isDangerous());
}

void RouterGridTest::constructor_bombAt3And5InGrid_noPlayerAt3And5()
{
	BombState bomb(*m_bombIdCreator, 0);
	bomb.setPosition(Point(3, 5));
	m_grid->addBombAtPlace(bomb);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(3, 5));
	CPPUNIT_ASSERT(!gridField.isPlayer());
}

void RouterGridTest::constructor_looseWallAt7And5InGrid_looseWallAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(gridField.isLooseWall());
}

void RouterGridTest::constructor_looseWallAt7And5InGrid_noSolidWallAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isSolidWall());
}

void RouterGridTest::constructor_looseWallAt7And5InGrid_noBombAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isBomb());
}

void RouterGridTest::constructor_looseWallAt7And5InGrid_notDangerousAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_looseWallAt7And5InGrid_noPlayerAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeLoose, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isPlayer());
}

void RouterGridTest::constructor_solidWallAt7And5InGrid_noLooseWallAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isLooseWall());
}

void RouterGridTest::constructor_solidWallAt7And5InGrid_solidWallAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(gridField.isSolidWall());
}

void RouterGridTest::constructor_solidWallAt7And5InGrid_noBombAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isBomb());
}

void RouterGridTest::constructor_solidWallAt7And5InGrid_notDangerousAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}

void RouterGridTest::constructor_solidWallAt7And5InGrid_noPlayerAt7And5()
{
	WallState wall(*m_wallIdCreator, WallState::WallTypeSolid, Point(7, 5));
	m_grid->addWallAtPlace(wall);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(7, 5));
	CPPUNIT_ASSERT(!gridField.isPlayer());
}

void RouterGridTest::constructor_powerUpAt8And9InGrid_noSolidWallAt8And9()
{
	PowerUpState powerUp(*m_powerUpIdCreator, Point(8, 9));
	m_grid->addPowerUpAtPlace(powerUp);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 9));
	CPPUNIT_ASSERT(!gridField.isSolidWall());
}

void RouterGridTest::constructor_powerUpAt8And9InGrid_noLooseWallAt8And9()
{
	PowerUpState powerUp(*m_powerUpIdCreator, Point(8, 9));
	m_grid->addPowerUpAtPlace(powerUp);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 9));
	CPPUNIT_ASSERT(!gridField.isLooseWall());
}

void RouterGridTest::constructor_powerUpAt8And9InGrid_noPlayerAt8And9()
{
	PowerUpState powerUp(*m_powerUpIdCreator, Point(8, 9));
	m_grid->addPowerUpAtPlace(powerUp);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 9));
	CPPUNIT_ASSERT(!gridField.isPlayer());
}

void RouterGridTest::constructor_powerUpAt8And9InGrid_noBombAt8And9()
{
	PowerUpState powerUp(*m_powerUpIdCreator, Point(8, 9));
	m_grid->addPowerUpAtPlace(powerUp);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 9));
	CPPUNIT_ASSERT(!gridField.isBomb());
}

void RouterGridTest::constructor_powerUpAt8And9InGrid_notDangerousAt8And9()
{
	PowerUpState powerUp(*m_powerUpIdCreator, Point(8, 9));
	m_grid->addPowerUpAtPlace(powerUp);

	RouterGrid routerGrid(*m_grid);

	const RouterGridField &gridField = routerGrid.getField(GridPoint(8, 9));
	CPPUNIT_ASSERT(!gridField.isDangerous());
}