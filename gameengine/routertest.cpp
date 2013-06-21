#include "gameengine/routertest.h"
#include "gameengine/router.h"
#include "gameengine/grid.h"
#include "common/leveldefinition.h"
#include "common/gamestate.h"
#include "common/uniqueidcreator.h"
#include "common/bombstate.h"

using namespace GameEngine;
using namespace Common;

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

	Route route = m_router->getRouteToPlayer(GridPoint(7, 4));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionLeft, route.getDirection());
}

void RouterTest::getRouteToPlayer_secondPlayerIsRightAndDirectWayBlocked_distanceIsWayAroundObstacle()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 0, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 2, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 3, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 6, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 8, 4);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 5));

	Route route = m_router->getRouteToPlayer(GridPoint(5, 4));

	CPPUNIT_ASSERT_EQUAL((unsigned int)13, route.getDistance());
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

	Route route = m_router->getRouteToPlayer(GridPoint(5, 5));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionNone, route.getDirection());
}

void RouterTest::getRouteToPlayer_jailedByWallsAtBorder_distanceIs0()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 0, 1);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 8));

	Route route = m_router->getRouteToPlayer(GridPoint(0, 0));

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, route.getDistance());
}

void RouterTest::getRouteToPlayer_jailedByWallsAtBorder_directionIsNone()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 0, 1);
	createRouter(level);
	PlayerState &playerTwo = getSecondPlayer();
	playerTwo.setPosition(Point(10, 8));

	Route route = m_router->getRouteToPlayer(GridPoint(0, 0));

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionNone, route.getDirection());
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

	m_grid = new Grid(level.getLevelHeight(), level.getLevelWidth());
	m_gameState = new GameState(level, level.getPlayerStartPositionCount(), *m_playerIdCreator, *m_wallIdCreator);
	const PlayerState &player = m_gameState->getFirstPlayerState();
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

