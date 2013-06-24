#include "gameengine/routertest.h"
#include "gameengine/router.h"
#include "common/grid.h"
#include "common/leveldefinition.h"
#include "common/gamestate.h"
#include "common/uniqueidcreator.h"
#include "common/bombstate.h"
#include <vector>

using namespace GameEngine;
using namespace Common;
using namespace std;

void RouterTest::constructor_validGrid_gridHasOneObserver()
{
	CPPUNIT_ASSERT_EQUAL((size_t)1, m_grid->getObserverCount());
}

void RouterTest::destructor_empty_gridHasNoObserver()
{
	delete m_router;
	m_router = 0;

	CPPUNIT_ASSERT_EQUAL((size_t)0, m_grid->getObserverCount());
}

void RouterTest::getRouteToPlayer_secondPlayerTwoFieldsLeft_distanceIs2()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(5, 4));
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(7, 4));

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, route.getDistance());
}

void RouterTest::getRouteToPlayer_secondPlayerTwoFieldsLeft_directionIsLeft()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(5, 4));
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(7, 4));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionLeft, route.getDirection());
}

void RouterTest::getRouteToPlayer_secondPlayerIsRightAndDirectWayBlocked_distanceIsWayAroundObstacle()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 6);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 7);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 8);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 5));
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(5, 4));

	CPPUNIT_ASSERT_EQUAL((unsigned int)14, route.getDistance());
}

void RouterTest::getRouteToPlayer_secondPlayerIsRightButRightAndBelowIsWall_directionIsUp()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 5);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(6, 5));
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(4, 5));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionUp, route.getDirection());
}

void RouterTest::getRouteToPlayer_noWayPossible_directionIsNone()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 6);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 6, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 4, 5);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 8));
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(5, 5));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionNone, route.getDirection());
}

void RouterTest::getRouteToPlayer_noWayPossible_distanceIs0()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 6);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 6, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 4, 5);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 8));
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(5, 5));

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, route.getDistance());
}

void RouterTest::getRouteToPlayer_bombInTheWay_distanceIsWayAroundBomb()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 5));
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(7, 5));
	m_gameState->addBomb(bomb);
	m_grid->addBombAtPlace(*bomb);
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(5, 5));

	CPPUNIT_ASSERT_EQUAL((unsigned int)9, route.getDistance());
}

void RouterTest::getRouteToPlayer_wayBlockedByBomb_distanceIs0()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 5));
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(7, 6));
	bomb->setDestructionRange(100);
	m_gameState->addBomb(bomb);
	m_grid->addBombAtPlace(*bomb);
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(5, 5));

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, route.getDistance());
}

void RouterTest::getRouteToPlayer_wayBlockedByBomb_directionIsNone()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 5));
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(7, 6));
	bomb->setDestructionRange(100);
	m_gameState->addBomb(bomb);
	m_grid->addBombAtPlace(*bomb);
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(5, 5));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionNone, route.getDirection());
}

void RouterTest::getRouteToPlayer_jailedByWallsAtBorder_distanceIs0()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 0, 1);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 8));
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(0, 0));

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, route.getDistance());
}

void RouterTest::getRouteToPlayer_jailedByWallsAtBorder_directionIsNone()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 0, 1);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 8));
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToPlayer(GridPoint(0, 0));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionNone, route.getDirection());
}

void RouterTest::getRouteToNotDangerousField_playerRightAtBomb_distanceIs2()
{
	const PlayerState &player = getFirstPlayer();
	BombState *bomb = new BombState(*m_bombIdCreator, 0);
	bomb->setPosition(Point(player.getPosition()));
	m_gameState->addBomb(bomb);
	m_grid->addBombAtPlace(*bomb);
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToNotDangerousField(player.getPosition());

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, route.getDistance());
}

void RouterTest::getRouteToNotDangerousField_playerPositionNotDangerous_directionIsNone()
{
	const PlayerState &player = getFirstPlayer();
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToNotDangerousField(player.getPosition());

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionNone, route.getDirection());
}

void RouterTest::getRouteToNotDangerousField_playerPositionNotDangerous_distanceIs0()
{
	const PlayerState &player = getFirstPlayer();
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToNotDangerousField(player.getPosition());

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, route.getDistance());
}

void RouterTest::getRouteToLooseWall_looseWallThreeFieldsAbovePlayer_distanceIs3()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 7, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 6);
	createRouter(level);
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToLooseWall(GridPoint(7, 3));

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, route.getDistance());
}

void RouterTest::getRouteToLooseWall_looseWallThreeFieldsAbovePlayer_directionIsUp()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 7, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 6);
	createRouter(level);
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToLooseWall(GridPoint(7, 3));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionUp, route.getDirection());
}

void RouterTest::getRouteToLooseWall_looseWallTwoFieldsLeftOfPlayer_distanceIs2()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 7, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 5);
	createRouter(level);
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToLooseWall(GridPoint(7, 5));

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, route.getDistance());
}

void RouterTest::getRouteToLooseWall_looseWallTwoFieldsLeftOfPlayer_directionIsLeft()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 7, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 5);
	createRouter(level);
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToLooseWall(GridPoint(7, 5));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionLeft, route.getDirection());
}

void RouterTest::getRouteToLooseWall_looseWallTwoFieldsBelowOfPlayer_distanceIs2()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 7, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 3);
	createRouter(level);
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToLooseWall(GridPoint(7, 5));

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, route.getDistance());
}

void RouterTest::getRouteToLooseWall_looseWallTwoFieldsBelowOfPlayer_directionIsDown()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 7, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 3);
	createRouter(level);
	m_router->updatePlayerFields();

	Route route = m_router->getRouteToLooseWall(GridPoint(7, 5));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionDown, route.getDirection());
}

void RouterTest::setUp()
{
	m_playerIdCreator = new UniqueIdCreator();
	m_wallIdCreator = new UniqueIdCreator();
	m_bombIdCreator = new UniqueIdCreator();
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 7, 8);
	createRouter(level);
}

void RouterTest::tearDown()
{
	delete m_router;
	m_router = 0;
	delete m_gameState;
	m_gameState = 0;
	delete m_grid;
	m_grid = 0;
	delete m_wallIdCreator;
	m_wallIdCreator = 0;
	delete m_playerIdCreator;
	m_playerIdCreator = 0;
	delete m_bombIdCreator;
	m_bombIdCreator = 0;
}

void RouterTest::createRouter(const LevelDefinition &level)
{
	delete m_router;
	delete m_grid;
	delete m_gameState;

	m_grid = new Grid(level.getHeight(), level.getWidth());
	m_gameState = new GameState(level, level.getPlayerStartPositionCount(), *m_playerIdCreator, *m_wallIdCreator);
	const PlayerState &player = m_gameState->getFirstPlayerState();
	vector<const WallState*> walls = m_gameState->getAllChangedWalls();

	for (vector<const WallState*>::const_iterator i = walls.begin(); i != walls.end(); ++i)
		m_grid->addWallAtPlace(**i);

	m_router = new Router(*m_grid, *m_gameState, player.getId());
}

PlayerState &RouterTest::getFirstPlayer()
{
	return m_gameState->getFirstPlayerState();
}

PlayerState &RouterTest::getSecondPlayer()
{
	return m_gameState->getSecondPlayerState();
}

