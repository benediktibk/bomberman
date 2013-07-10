#include "gameengine/computerenemyinputfetcherhardtest.h"
#include "gameengine/computerenemyinputfetcherhard.h"
#include "common/gamestate.h"
#include "common/grid.h"
#include "common/leveldefinition.h"
#include "common/uniqueidcreator.h"

using namespace GameEngine;
using namespace Common;
using namespace std;

void ComputerEnemyInputFetcherHardTest::getInputState_movingToFieldRightBesidePlayerButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed()
{
	m_otherPlayer->setPosition(Point(0, 0));
	m_ownPlayer->setPosition(Point(1.7, 0));
	m_ownPlayer->setDirectionLeft();

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_movingToFieldRightBesidePlayerCloseEnoughToPlaceBomb_spaceKeyPressed()
{
	m_otherPlayer->setPosition(Point(0, 0));
	m_ownPlayer->setPosition(Point(1.3, 0));
	m_ownPlayer->setDirectionLeft();

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_movingToFieldRightBesideLooseFieldButNotYetAtPositionToPlaceBomb_spaceKeyNotPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 3, 1);
	createInputFetcher(level);
	m_ownPlayer->setPosition(Point(1.3, 1));
	m_ownPlayer->setDirectionLeft();

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_movingToFieldRightBesideLooseFieldCloseEnoughToPlaceBomb_spaceKeyPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 3, 1);
	createInputFetcher(level);
	m_ownPlayer->setPosition(Point(1.7, 1));
	m_ownPlayer->setDirectionRight();

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_onDangerousFieldAndShortestWayOutLeftAndRightOtherPlayerAndDownLooseWall_leftKeyPressed()
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

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(input.isLeftKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_looseWallRightAndOtherPlayerUp_upKeyPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 3);
	createInputFetcher(level);
	m_ownPlayer->setPosition(Point(3, 3));
	m_otherPlayer->setPosition(Point(3, 5));

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(input.isUpKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_looseWallRight_rightKeyPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 3);
	createInputFetcher(level);

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(input.isRightKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_powerUpOnDangerousField_noMovementButtonPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	createInputFetcher(level);
	BombState *bomb = new BombState(*m_bombIdCreator, 0, Point(7, 7), 1);
	m_gameState->addBomb(bomb);
	m_grid->addBombAtPlace(*bomb);
	PowerUpMaxBombRangeState *powerUp = new PowerUpMaxBombRangeState(*m_powerUpIdCreator, Point(7, 8));
	m_gameState->addPowerUp(powerUp);
	m_grid->addPowerUpAtPlace(*powerUp);

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isMovementButtonPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_onSaveFieldAsPossibleTargetToBlowUpWallButCantEscapeDirect_spaceKeyNotPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	createInputFetcher(level);
	BombState *bomb = new BombState(*m_bombIdCreator, 0, Point(1, 1), 10);
	m_gameState->addBomb(bomb);
	m_grid->addBombAtPlace(*bomb);

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_besideSaveFieldAsPossibleTargetToBlowUpWallButCantEscapeDirect_noMovementButtonPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 0, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	createInputFetcher(level);
	BombState *bomb = new BombState(*m_bombIdCreator, 0, Point(1, 2), 10);
	m_gameState->addBomb(bomb);
	m_grid->addBombAtPlace(*bomb);

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isMovementButtonPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_besideSaveFieldAsPossibleTargetToBlowUpEnemyButCantEscapeDirect_noMovementButtonPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 0, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createInputFetcher(level);
	BombState *bomb = new BombState(*m_bombIdCreator, 0, Point(1, 2), 10);
	m_gameState->addBomb(bomb);
	m_grid->addBombAtPlace(*bomb);

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isMovementButtonPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_besideSaveFieldAsPossibleTargetToBlowUpWallButToSlowToEscape_noMovementButtonPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 2, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 2, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 6);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 7);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 8);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 9);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 10);
	createInputFetcher(level);
	PlayerState &player = m_gameState->getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(20);

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isMovementButtonPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_besideSaveFieldAsPossibleTargetToBlowUpEnemyButToSlowToEscape_noMovementButtonPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 2, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 2, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 6);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 7);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 8);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 9);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 10);
	createInputFetcher(level);
	PlayerState &player = m_gameState->getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(20);

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isMovementButtonPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_onSaveFieldAsPossibleTargetToBlowUpWallButToSlowToEscape_spaceKeyNotPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 2, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 2, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 6);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 7);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 8);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 9);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 10);
	createInputFetcher(level);
	PlayerState &player = m_gameState->getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(20);

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_onSaveFieldAsPossibleTargetToBlowUpEnemyButToSlowToEscape_spaceKeyNotPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 2, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 2, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 6);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 7);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 8);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 9);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 10);
	createInputFetcher(level);
	PlayerState &player = m_gameState->getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(20);

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::getInputState_onSaveFieldAsPossibleTargetToBlowUpWallButCanEscapeDirectBecauseOfBombWithRange1_spaceKeyNotPressed()
{
	LevelDefinition level(13, 14);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	createInputFetcher(level);
	BombState *bomb = new BombState(*m_bombIdCreator, 0, Point(1, 2), 1);
	m_gameState->addBomb(bomb);
	m_grid->addBombAtPlace(*bomb);

	map<unsigned int, InputState> inputs = m_inputFetcher->getInputStates();
	InputState input = inputs.begin()->second;

	CPPUNIT_ASSERT(!input.isSpaceKeyPressed());
}

void ComputerEnemyInputFetcherHardTest::createInputFetcher(const LevelDefinition &level)
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
	m_gameState = new GameState(level, level.getPlayerStartPositionCount(), 0, *m_playerIdCreator, *m_wallIdCreator);
	m_ownPlayer = &(m_gameState->getFirstPlayerState());
	if (level.getPlayerStartPositionCount() > 1)
		m_otherPlayer = &(m_gameState->getSecondPlayerState());
	vector<const WallState*> walls = m_gameState->getAllChangedWalls();
	for (vector<const WallState*>::const_iterator i = walls.begin(); i != walls.end(); ++i)
		m_grid->addWallAtPlace(**i);
	m_inputFetcher = new ComputerEnemyInputFetcherHard(*m_grid, *m_gameState);
	vector<unsigned int> playerIDs;
	playerIDs.push_back(m_ownPlayer->getId());
	m_inputFetcher->setAllPossiblePlayerIDs(playerIDs);
}

void ComputerEnemyInputFetcherHardTest::setUp()
{
	m_playerIdCreator = new UniqueIdCreator();
	m_wallIdCreator = new UniqueIdCreator();
	m_bombIdCreator = new UniqueIdCreator();
	m_powerUpIdCreator = new UniqueIdCreator();
	LevelDefinition level(15, 12);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createInputFetcher(level);
}

void ComputerEnemyInputFetcherHardTest::tearDown()
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
	delete m_powerUpIdCreator;
	m_powerUpIdCreator = 0;
}