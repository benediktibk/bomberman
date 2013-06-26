#include "gameengine/computerenemyinputfetchertest.h"
#include "gameengine/computerenemyinputfetcher.h"
#include "common/gamestate.h"
#include "common/grid.h"
#include "common/leveldefinition.h"
#include "common/uniqueidcreator.h"

using namespace GameEngine;
using namespace Common;
using namespace std;

void ComputerEnemyInputFetcherTest::getInputState_movingToFieldRightBesidePlayerButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed()
{
	m_otherPlayer->setPosition(Point(0, 0));
	m_ownPlayer->setPosition(Point(1.7, 0));
	m_ownPlayer->setDirectionLeft();

	InputState input = m_inputFetcher->getInputState();

	CPPUNIT_ASSERT(!input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherTest::getInputState_movingToFieldRightBesidePlayerCloseEnoughToPlaceBomb_spaceKeyPressed()
{
	m_otherPlayer->setPosition(Point(0, 0));
	m_ownPlayer->setPosition(Point(1.3, 0));
	m_ownPlayer->setDirectionLeft();

	InputState input = m_inputFetcher->getInputState();

	CPPUNIT_ASSERT(input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherTest::getInputState_movingToFieldRightBesideLooseFieldButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 3, 1);
	createInputFetcher(level);
	m_ownPlayer->setPosition(Point(1.3, 1));
	m_ownPlayer->setDirectionLeft();

	InputState input = m_inputFetcher->getInputState();

	CPPUNIT_ASSERT(!input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherTest::getInputState_movingToFieldRightBesideLooseFieldCloseEnoughToPlaceBomb_spaceKeyPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 3, 1);
	createInputFetcher(level);
	m_ownPlayer->setPosition(Point(1.7, 1));
	m_ownPlayer->setDirectionRight();

	InputState input = m_inputFetcher->getInputState();

	CPPUNIT_ASSERT(input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherTest::getInputState_onDangerousFieldAndShortestWayOutLeftAndRightOtherPlayerAndDownLooseWall_leftKeyPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 3, 1);
	createInputFetcher(level);
	BombState *bombOne = new BombState(*m_bombIdCreator, 0, Point(4, 3), 1);
	BombState *bombTwo = new BombState(*m_bombIdCreator, 0, Point(4, 2), 1);
	BombState *bombThree = new BombState(*m_bombIdCreator, 0, Point(4, 4), 1);
	m_gameState->addBomb(bombOne);
	m_gameState->addBomb(bombTwo);
	m_gameState->addBomb(bombThree);
	m_grid->addBombAtPlace(*bombOne);
	m_grid->addBombAtPlace(*bombTwo);
	m_grid->addBombAtPlace(*bombThree);
	m_ownPlayer->setPosition(Point(3, 3));
	m_otherPlayer->setPosition(Point(5, 3));

	InputState input = m_inputFetcher->getInputState();

	CPPUNIT_ASSERT(input.isLeftKeyPressed());
}

void ComputerEnemyInputFetcherTest::getInputState_looseWallRightAndOtherPlayerUp_upKeyPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 3);
	createInputFetcher(level);
	m_ownPlayer->setPosition(Point(3, 3));
	m_otherPlayer->setPosition(Point(3, 5));

	InputState input = m_inputFetcher->getInputState();

	CPPUNIT_ASSERT(input.isUpKeyPressed());
}

void ComputerEnemyInputFetcherTest::getInputState_looseWallRight_rightKeyPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 3);
	createInputFetcher(level);

	InputState input = m_inputFetcher->getInputState();

	CPPUNIT_ASSERT(input.isRightKeyPressed());
}

void ComputerEnemyInputFetcherTest::createInputFetcher(const LevelDefinition &level)
{
	delete m_inputFetcher;
	m_inputFetcher = 0;
	delete m_gameState;
	m_gameState = 0;
	delete m_grid;
	m_grid = 0;
	m_otherPlayer = 0;
	m_ownPlayer = 0;

	m_grid = new Grid(level.getHeight(), level.getWidth());
	m_gameState = new GameState(level, level.getPlayerStartPositionCount(), *m_playerIdCreator, *m_wallIdCreator);
	m_ownPlayer = &(m_gameState->getFirstPlayerState());
	if (level.getPlayerStartPositionCount() > 1)
		m_otherPlayer = &(m_gameState->getSecondPlayerState());
	vector<const WallState*> walls = m_gameState->getAllChangedWalls();
	for (vector<const WallState*>::const_iterator i = walls.begin(); i != walls.end(); ++i)
		m_grid->addWallAtPlace(**i);
	m_inputFetcher = new ComputerEnemyInputFetcher(*m_grid, *m_gameState, m_ownPlayer->getId());
}

void ComputerEnemyInputFetcherTest::setUp()
{
	m_playerIdCreator = new UniqueIdCreator();
	m_wallIdCreator = new UniqueIdCreator();
	m_bombIdCreator = new UniqueIdCreator();
	LevelDefinition level(15, 12);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createInputFetcher(level);
}

void ComputerEnemyInputFetcherTest::tearDown()
{
	delete m_inputFetcher;
	m_inputFetcher = 0;
	delete m_gameState;
	m_gameState = 0;
	delete m_grid;
	m_grid = 0;
	delete m_playerIdCreator;
	m_playerIdCreator = 0;
	delete m_wallIdCreator;
	m_wallIdCreator = 0;
	delete m_bombIdCreator;
	m_bombIdCreator = 0;
}
