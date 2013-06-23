#include "gameengine/computerenemyinputfetchertest.h"
#include "gameengine/computerenemyinputfetcher.h"
#include "common/gamestate.h"
#include "common/grid.h"
#include "common/leveldefinition.h"
#include "common/uniqueidcreator.h"

using namespace GameEngine;
using namespace Common;

void ComputerEnemyInputFetcherTest::getInputState_movingToFieldRightBesidePlayerButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed()
{
	m_otherPlayer->setPosition(Point(0, 0));
	m_ownPlayer->setPosition(Point(0.7, 0));
	m_ownPlayer->setDirectionLeft();

	InputState input = m_inputFetcher->getInputState();

	CPPUNIT_ASSERT(!input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherTest::getInputState_movingToFieldRightBesidePlayerCloseEnoughToPlaceBomb_spaceKeyPressed()
{
	m_otherPlayer->setPosition(Point(0, 0));
	m_ownPlayer->setPosition(Point(0.3, 0));
	m_ownPlayer->setDirectionLeft();

	InputState input = m_inputFetcher->getInputState();

	CPPUNIT_ASSERT(input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherTest::setUp()
{
	m_playerIdCreator = new UniqueIdCreator();
	m_wallIdCreator = new UniqueIdCreator();
	LevelDefinition level(15, 12);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	m_grid = new Grid(level.getHeight(), level.getWidth());
	m_gameState = new GameState(level, 2, *m_playerIdCreator, *m_wallIdCreator);
	m_ownPlayer = &(m_gameState->getFirstPlayerState());
	m_otherPlayer = &(m_gameState->getSecondPlayerState());
	m_inputFetcher = new ComputerEnemyInputFetcher(*m_grid, *m_gameState, m_ownPlayer->getId());
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
}
