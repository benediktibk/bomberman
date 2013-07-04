#include "gameengine/coveredbyloosewalldecidertest.h"
#include "gameengine/coveredbyloosewalldecider.h"
#include "gameengine/routergridfield.h"
#include "gameengine/router.h"
#include "common/grid.h"
#include "common/gamestate.h"
#include "common/leveldefinition.h"
#include "common/bombstate.h"

using namespace GameEngine;
using namespace Common;

void CoveredByLooseWallDeciderTest::decide_defaultField_false()
{
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 5);
	createRouter(level);
	RouterGridField field(GridPoint(4, 3));
	RouterGridField previousField(GridPoint(4, 4));
	CoveredByLooseWallDecider decider(*m_router, 1, false);

	CPPUNIT_ASSERT(!decider.decide(field, previousField, true));
}

void CoveredByLooseWallDeciderTest::decide_looseWallAtField_true()
{
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 5);
	createRouter(level);
	RouterGridField field(GridPoint(4, 3));
	RouterGridField previousField(GridPoint(4, 4));
	CoveredByLooseWallDecider decider(*m_router, 1, false);
	field.setLooseWall(true);

	CPPUNIT_ASSERT(decider.decide(field, previousField, true));
}

void CoveredByLooseWallDeciderTest::decide_looseWallButCanNotEscape_false()
{
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 5);
	createRouter(level);
	RouterGridField field(GridPoint(0, 0));
	RouterGridField previousField(GridPoint(1, 0));
	CoveredByLooseWallDecider decider(*m_router, 10, true);
	field.setLooseWall(true);
	BombState *bomb = new BombState(*m_bombIdCreator, 0, Point(3, 1), 10);
	m_gameState->addBomb(bomb);
	m_grid->addBombAtPlace(*bomb);

	CPPUNIT_ASSERT(!decider.decide(field, previousField, true));
}

void CoveredByLooseWallDeciderTest::createRouter(const LevelDefinition &level)
{
	tearDown();

	m_grid = new Grid(10, 10);
	m_gameState = new GameState(level, level.getPlayerStartPositionCount(), 0, *m_playerIdCreator, *m_wallIdCreator);
	m_router = new Router(*m_grid, *m_gameState, m_gameState->getFirstPlayerState().getId());
}

void CoveredByLooseWallDeciderTest::setUp()
{
	tearDown();
}

void CoveredByLooseWallDeciderTest::tearDown()
{
	delete m_router;
	m_router = 0;
	delete m_gameState;
	m_gameState = 0;
	delete m_grid;
	m_grid = 0;
}

CoveredByLooseWallDeciderTest::CoveredByLooseWallDeciderTest() :
	m_playerIdCreator(new UniqueIdCreator()),
	m_wallIdCreator(new UniqueIdCreator()),
	m_bombIdCreator(new UniqueIdCreator()),
	m_grid(0),
	m_gameState(0),
	m_router(0)
{ }

CoveredByLooseWallDeciderTest::~CoveredByLooseWallDeciderTest()
{
	tearDown();
	delete m_playerIdCreator;
	m_playerIdCreator = 0;
	delete m_wallIdCreator;
	m_wallIdCreator = 0;
	delete m_bombIdCreator;
	m_bombIdCreator = 0;
}
