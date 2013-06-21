#include "gameengine/routertest.h"
#include "gameengine/router.h"
#include "gameengine/grid.h"
#include "common/leveldefinition.h"
#include "common/gamestate.h"
#include "common/uniqueidcreator.h"

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

void RouterTest::setUp()
{
	m_playerIdCreator = new UniqueIdCreator();
	m_wallIdCreator = new UniqueIdCreator();
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

