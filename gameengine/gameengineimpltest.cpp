#include "gameengineimpltest.h"
#include "common/powerupmaxbombstate.h"

using namespace std;
using namespace GameEngine;
using namespace Common;

void GameEngineImplTest::updateGameState_UpKeyPressed_PlayerDirectionUp()
{
	InputState input;

	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionUp, player.getDirection());
}

void GameEngineImplTest::updateGameState_DownKeyPressed_PlayerDirectionDown()
{
	InputState input;

	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionDown, player.getDirection());
}

void GameEngineImplTest::updateGameState_LeftKeyPressed_PlayerDirectionLeft()
{
	InputState input;

	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionLeft, player.getDirection());
}

void GameEngineImplTest::updateGameState_RightKeyPressed_PlayerDirectionRight()
{
	InputState input;

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionRight, player.getDirection());
}

void GameEngineImplTest::updateGameState_oneBombPlaced_bombPositionIsSameAsPlayerPosition()
{
	InputState input;
	const BombState *bomb;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	bomb = game.getAllChangedBombs().front();

	CPPUNIT_ASSERT(player.getPosition().fuzzyEqual(bomb->getPosition(), 0.001));
}

void GameEngineImplTest::updateGameState_oneBombPlaced_bombLifeTimeIs2()
{
	InputState input;
	const BombState *bomb;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1);
	const GameState &game = m_gameEngine->getGameState();
	bomb = game.getAllChangedBombs().front();

	CPPUNIT_ASSERT_EQUAL((double)2, bomb->getLifeTime());
}

void GameEngineImplTest::updateGameState_onlyOneBombPlaced_whenPressingSpacebar()
{
	InputState input;
	GameState &game = m_gameEngine->getGameState();
	PlayerState &player = game.getFirstPlayerState();
	player.increaseMaxBombs();

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1);
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1.5*m_defaultTimeForOneField);

	CPPUNIT_ASSERT_EQUAL((size_t)1, game.getBombCount());
}

void GameEngineImplTest::updateGameState_twoBombsPlacedAndOneDestroyed_bombCountIs1()
{
	InputState input;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 3.1);
	input.setSpaceKeyPressed();
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)1, game.getBombCount());
}

void GameEngineImplTest::getHeight_HeightOfLevelDefinition_HeightOfGamestate()
{
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL(level.getHeight(), game.getHeight());
}

void GameEngineImplTest::getWidth_WidthOfLevelDefinition_WidthOfGamestate()
{
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL(level.getWidth(), game.getWidth());
}

void GameEngineImplTest::updateGameState_tryToMoveThroughRightBorder_playerPositionIsAtRightBorder()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;
	input.setRightKeyPressed();
	setFirstPlayerInput(input);

	m_gameEngine->updateGameState(m_inputStates, 10);

	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &playerState = game.getFirstPlayerState();
	Point positionShouldBe(3, 0);
	Point positionReal(playerState.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_tryToMoveThroughUpperBorder_playerPositionIsAtUpperBorder()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;
	input.setUpKeyPressed();
	setFirstPlayerInput(input);

	m_gameEngine->updateGameState(m_inputStates, 10);

	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &playerState = game.getFirstPlayerState();
	Point positionShouldBe(0, 3);
	Point positionReal(playerState.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_tryToMoveThroughLowerBorder_playerPositionIsAtLowerBorder()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;
	input.setDownKeyPressed();
	setFirstPlayerInput(input);

	m_gameEngine->updateGameState(m_inputStates, 10);

	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &playerState = game.getFirstPlayerState();
	Point positionShouldBe(0, 0);
	Point positionReal(playerState.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_tryToMoveThroughLeftBorder_playerPositionIsAtLeftBorder()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);

	m_gameEngine->updateGameState(m_inputStates, 10);

	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &playerState = game.getFirstPlayerState();
	Point positionShouldBe(0, 0);
	Point positionReal(playerState.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::getWallCount_Create4x4LevelWith2Wall_WallCountIs2()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 3, 3);
	createGameEngine(level, 1, 0);

	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)2, game.getWallCount());
}

void GameEngineImplTest::getWallPosition_Create4x4LevelWithWallPosition2And2_WallPosition2And2()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 2, 2);
	createGameEngine(level, 1, 0);
	const WallState *wall;
	const Point point(2,2);

	const GameState &game = m_gameEngine->getGameState();
	wall = game.getAllChangedWalls().front();

	CPPUNIT_ASSERT_EQUAL((const Point)point, wall->getPosition());
}

void GameEngineImplTest::getWallType_Create4x4LevelWallWithWallType_WallTypeIsLoose()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 2, 2);
	createGameEngine(level, 1, 0);
	const WallState *wall;

	const GameState &game = m_gameEngine->getGameState();
	wall = game.getAllChangedWalls().front();

	CPPUNIT_ASSERT_EQUAL(WallState::WallTypeLoose, wall->getWallType());
}

void GameEngineImplTest::updateGameState_halfTheTimeOfTheMovementToTheNextGridFieldButtonPressed_playerReachesGridPoint()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);

	Point positionShouldBe(1, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void GameEngineImplTest::updateGameState_playerVerticalBetweenTwoFieldsAndUpPressed_playerKeepsDirection()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);

	Point positionShouldBe(1, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void GameEngineImplTest::getWallCount_Create4x4LevelWith2WallsOneWallInRangeOfBombAndBombExplodes_WallCount1()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	createGameEngine(level, 1, 0);
	InputState input;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	m_gameEngine->updateGameState(m_inputStates, 3.1);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);

	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)1, game.getWallCount());
}

void GameEngineImplTest::updateGameState_Create4x4LevelWithSolidWallAndLetBombExplode_wallCountIs1()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 0);
	createGameEngine(level, 1, 0);
	InputState input;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 3.1);
	m_gameEngine->updateGameState(m_inputStates, 0);

	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)1, game.getWallCount());
}

void GameEngineImplTest::updateGameState_placeBombAndWaitTillItExploded_bombCountIs0()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 3.1);
	m_gameEngine->updateGameState(m_inputStates, 0);

	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)0, game.getBombCount());
}

void GameEngineImplTest::updateGameState_placeBombAtUpperBorder_bombCountIs0()
{
	LevelDefinition level(10, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;

	input.setUpKeyPressed();
	m_gameEngine->updateGameState(m_inputStates, 100);
	input.setUpKeyNotPressed();
	input.setSpaceKeyPressed();
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	m_gameEngine->updateGameState(m_inputStates, 10);
	m_gameEngine->updateGameState(m_inputStates, 0);

	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)0, game.getBombCount());
}

void GameEngineImplTest::updateGameState_playerSurroundedByWallsAndTriesToMoveUp_playerMovedUp()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	createGameEngine(level, 1, 0);
	InputState input;
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &playerState = gameState.getFirstPlayerState();
	Point initialPosition = playerState.getPosition();

	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 10);

	Point newPosition = playerState.getPosition();

	CPPUNIT_ASSERT(newPosition.getY() > initialPosition.getY());
}

void GameEngineImplTest::updateGameState_playerSurroundedByWallsAndTriesToMoveRight_playerMovedRight()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	createGameEngine(level, 1, 0);
	InputState input;
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &playerState = gameState.getFirstPlayerState();
	Point initialPosition = playerState.getPosition();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 10);

	Point newPosition = playerState.getPosition();

	CPPUNIT_ASSERT(newPosition.getX() > initialPosition.getX());
}

void GameEngineImplTest::updateGameState_moveRightAndToUpperBorderAndBackAndTryToGetRightBetweenTwoWalls_playerMovedRight()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 3, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 3, 4);
	createGameEngine(level, 1, 0);
	InputState input;
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &playerState = gameState.getFirstPlayerState();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1.5*m_defaultTimeForOneField);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 20*m_defaultTimeForOneField);
	input.setUpKeyNotPressed();
	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 5.5*m_defaultTimeForOneField);
	input.setDownKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	Point newPosition = playerState.getPosition();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, newPosition.getX(), 0.05);
}


void GameEngineImplTest::updateGameState_moveTowardsWallAndAgainAway_playerPositionIsCorrect()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &playerState = gameState.getFirstPlayerState();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setUpKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField*2);
	input.setLeftKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField*2);
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	Point realPosition = playerState.getPosition();
	Point positionShouldBe(1, 1);

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(realPosition, 0.05));
}

void GameEngineImplTest::updateGameState_pressRightAndThenUp_playerKeepsDirection()
{
	InputState input;
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &playerState = gameState.getFirstPlayerState();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);
	input.setRightKeyNotPressed();
	input.setUpKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	Point positionShouldBe(2, 0);
	Point positionReal(playerState.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_pressLeftAndThenDown_playerKeepsDirection()
{
	InputState input;
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &playerState = gameState.getFirstPlayerState();
	playerState.setPosition(Point(5, 1));

	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);
	input.setLeftKeyNotPressed();
	input.setDownKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	Point positionShouldBe(3, 1);
	Point positionReal(playerState.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_pressUpAndThenRight_playerKeepsDirection()
{
	InputState input;
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &playerState = gameState.getFirstPlayerState();

	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);
	input.setUpKeyNotPressed();
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	Point positionShouldBe(0, 2);
	Point positionReal(playerState.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGamestate_pressDownAndThenLeft_playerKeepsDirection()
{
	InputState input;
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &playerState = gameState.getFirstPlayerState();
	playerState.setPosition(Point(3, 5));

	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);
	input.setDownKeyNotPressed();
	input.setLeftKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	Point positionShouldBe(3, 3);
	Point positionReal(playerState.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_movementOfSecondPlayer_positionOfSecondPlayerIsCorrect()
{
	InputState input;
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createGameEngine(level, 2, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &firstPlayer = gameState.getFirstPlayerState();
	PlayerState &secondPlayer = gameState.getSecondPlayerState();
	firstPlayer.setPosition(Point(0, 0));
	secondPlayer.setPosition(Point(0, 1));

	input.setRightKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	Point positionShouldBe(1, 1);
	Point positionReal(secondPlayer.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_movementOfSecondPlayer_firstPlayerDoesntMove()
{
	InputState input;
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createGameEngine(level, 2, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &firstPlayer = gameState.getFirstPlayerState();
	PlayerState &secondPlayer = gameState.getSecondPlayerState();
	firstPlayer.setPosition(Point(0, 0));
	secondPlayer.setPosition(Point(0, 1));

	input.setRightKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	Point positionShouldBe(0, 0);
	Point positionReal(firstPlayer.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsRight_explodedBombRangeRightIs1()
{
	InputState input;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 6, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(3);

	input.setSpaceKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);

	vector<const ExplodedBombState*> explodedBombs = gameState.getAllChangedExplodedBombs();
	const ExplodedBombState &explodedBomb = *(explodedBombs.front());

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, explodedBomb.getDestructionRangeRight());
}

void GameEngineImplTest::updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsLeft_explodedBombRangeLeftIs1()
{
	InputState input;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 2, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(3);

	input.setSpaceKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);

	vector<const ExplodedBombState*> explodedBombs = gameState.getAllChangedExplodedBombs();
	const ExplodedBombState &explodedBomb = *(explodedBombs.front());

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, explodedBomb.getDestructionRangeLeft());
}

void GameEngineImplTest::updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsDown_explodedBombRangeDownIs1()
{
	InputState input;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 4, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(3);

	input.setSpaceKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);

	vector<const ExplodedBombState*> explodedBombs = gameState.getAllChangedExplodedBombs();
	const ExplodedBombState &explodedBomb = *(explodedBombs.front());

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, explodedBomb.getDestructionRangeDown());
}

void GameEngineImplTest::updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsUp_explodedBombRangeUpIs1()
{
	InputState input;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 4, 6);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(3);

	input.setSpaceKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);

	vector<const ExplodedBombState*> explodedBombs = gameState.getAllChangedExplodedBombs();
	const ExplodedBombState &explodedBomb = *(explodedBombs.front());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, explodedBomb.getDestructionRangeUp());
}

void GameEngineImplTest::updateGameState_bombWithRange3ExplodesWithLooseWallTwoFieldsRight_explodedBombRangeRightIs2()
{
	InputState input;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 6, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(3);

	input.setSpaceKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);

	vector<const ExplodedBombState*> explodedBombs = gameState.getAllChangedExplodedBombs();
	const ExplodedBombState &explodedBomb = *(explodedBombs.front());

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, explodedBomb.getDestructionRangeRight());
}

void GameEngineImplTest::updateGameState_bombWithRange3ExplodesWithLooseWallTwoFieldsLeft_explodedBombRangeLeftIs2()
{
	InputState input;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 2, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(3);

	input.setSpaceKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);

	vector<const ExplodedBombState*> explodedBombs = gameState.getAllChangedExplodedBombs();
	const ExplodedBombState &explodedBomb = *(explodedBombs.front());

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, explodedBomb.getDestructionRangeLeft());
}

void GameEngineImplTest::updateGameState_bombWithRange3ExplodesWithLooseWallTwoFieldsDown_explodedBombRangeDownIs2()
{
	InputState input;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 4, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(3);

	input.setSpaceKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);

	vector<const ExplodedBombState*> explodedBombs = gameState.getAllChangedExplodedBombs();
	const ExplodedBombState &explodedBomb = *(explodedBombs.front());

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, explodedBomb.getDestructionRangeDown());
}

void GameEngineImplTest::updateGameState_bombWithRange3ExplodesWithLooseWallTwoFieldsUp_explodedBombRangeUpIs2()
{
	InputState input;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 4, 6);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(3);

	input.setSpaceKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);

	vector<const ExplodedBombState*> explodedBombs = gameState.getAllChangedExplodedBombs();
	const ExplodedBombState &explodedBomb = *(explodedBombs.front());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, explodedBomb.getDestructionRangeUp());
}

void GameEngineImplTest::updateGameState_playerWithDestructionRange5PlacesBomb_destructionRangeOfBombIs5()
{
	InputState input;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(5);

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);

	vector<const BombState*> bombs = gameState.getAllChangedBombs();
	const BombState &bomb = *(bombs.front());
	CPPUNIT_ASSERT_EQUAL((unsigned int)5, bomb.getDestructionRange());
}

void GameEngineImplTest::updateGameState_playerDiesByHisOwnBomb_playerCountIs0()
{
	InputState input;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	createGameEngine(level, 1, 0);

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField*100);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField*100);

	const GameState &gameState = m_gameEngine->getGameState();
	CPPUNIT_ASSERT_EQUAL((size_t)0, gameState.getPlayerCount());
}

void GameEngineImplTest::updateGameState_bombAtLowerEndExplodes_bombCountIs0()
{
	InputState input;
	LevelDefinition level(10, 15);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 0);
	createGameEngine(level, 1, 0);

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField*100);
	m_gameEngine->updateGameState(m_inputStates, 100);

	const GameState &gameState = m_gameEngine->getGameState();
	CPPUNIT_ASSERT_EQUAL((size_t)0, gameState.getBombCount());
}

void GameEngineImplTest::updateGameState_bombExplodesWithTwoLooseWallsDirectBehind_wallCountIs1()
{
	InputState input;
	LevelDefinition level(10, 15);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 4, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 3);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(100);

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);
	m_gameEngine->updateGameState(m_inputStates, 100);

	CPPUNIT_ASSERT_EQUAL((size_t)1, gameState.getWallCount());
}

void GameEngineImplTest::updateGameState_bombExplodesWithTwoLooseWallsBehindWithOneFieldFree_wallCountIs1()
{
	InputState input;
	LevelDefinition level(10, 15);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 4, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 6, 3);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(100);

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);
	m_gameEngine->updateGameState(m_inputStates, 100);

	CPPUNIT_ASSERT_EQUAL((size_t)1, gameState.getWallCount());
}

void GameEngineImplTest::updateGameState_bombExplodesWithPowerUpInRange_explosionRangeGoesThroughPowerUp()
{
	InputState input;
	LevelDefinition level(10, 15);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 8, 3);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	player.setDestructionRangeOfNewBombs(100);
	m_gameEngine->addPowerUpOfTypeAtPosition(PowerUpTypeMaxBomb, Point(5, 3));

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 100);

	vector<const ExplodedBombState*> explodedBombs = gameState.getAllChangedExplodedBombs();
	const ExplodedBombState &explodedBomb = *(explodedBombs.front());
	CPPUNIT_ASSERT_EQUAL((unsigned int)5, explodedBomb.getDestructionRangeRight());
}

void GameEngineImplTest::updateGameState_bombExplodesWithBombInRange_explosionRangeGoesThroughBomb()
{
	InputState input;
	LevelDefinition level(10, 15);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 8, 3);
	createGameEngine(level, 1, 0);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &player = gameState.getFirstPlayerState();
	double initialBombLifeTime = BombState::initialLifeTime();
	player.setDestructionRangeOfNewBombs(100);
	player.increaseMaxBombs();

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, initialBombLifeTime/2);
	m_gameEngine->updateGameState(m_inputStates, initialBombLifeTime*2);

	vector<const ExplodedBombState*> explodedBombs = gameState.getAllChangedExplodedBombs();
	const ExplodedBombState &firstExplodedBomb = *(explodedBombs.front());
	const ExplodedBombState &secondExplodedBomb = *(explodedBombs[1]);
	CPPUNIT_ASSERT(5 == firstExplodedBomb.getDestructionRangeRight() || 5 == secondExplodedBomb.getDestructionRangeRight());
}

void GameEngineImplTest::updateGameState_placeBombAndMoveOneFieldUpwards_playerIsOneFieldAboveTheBomb()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	InputState input;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setUpKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1.1*m_defaultTimeForOneField/2);

	Point positionShouldBe(0, 1);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_placeBombAndMoveOneFieldUpwardsAndSecondPlayer_playerIsOneFieldAboveTheBomb()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	createGameEngine(level, 2, 0);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &firstPlayer = game.getFirstPlayerState();
	const PlayerState &secondPlayer = game.getSecondPlayerState();
	const PlayerState *playerAsPointer = 0;
	if (firstPlayer.getPosition().fuzzyEqual(Point(0, 0), 0.05))
		playerAsPointer = &firstPlayer;
	else
		playerAsPointer = &secondPlayer;
	const PlayerState &player = *playerAsPointer;
	InputState input;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setUpKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	CPPUNIT_ASSERT(Point(0, 1).fuzzyEqual(player.getPosition(), 0.05));
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayRightToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(m_defaultTimeForOneField/2, m_gameEngine->getTimeTillOnePlayerReachesGridPoint(), 0.0001);
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayLeftToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2*10);
	input.setRightKeyNotPressed();
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(m_defaultTimeForOneField/2, m_gameEngine->getTimeTillOnePlayerReachesGridPoint(), 0.05);
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayUpToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;

	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(m_defaultTimeForOneField/2, m_gameEngine->getTimeTillOnePlayerReachesGridPoint(), 0.0001);
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayDownToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;

	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2*10);
	input.setUpKeyNotPressed();
	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(m_defaultTimeForOneField/2, m_gameEngine->getTimeTillOnePlayerReachesGridPoint(), 0.05);
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerStaysOnGridPoint_veryLong()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);

	m_gameEngine->updateGameState(m_inputStates, 10);

	CPPUNIT_ASSERT(m_gameEngine->getTimeTillOnePlayerReachesGridPoint() > 100000);
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerIsMovingButDirectOnGridField_timeToReachNextGridField()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);

	double time = m_gameEngine->getTimeTillOnePlayerReachesGridPoint();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(m_defaultTimeForOneField, time, 0.0001);
}

void GameEngineImplTest::updateGameState_keyPressedHalfWayToGridFieldAndEnoughTimeToReachIt_playerPositionIsGridField()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	InputState input;

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	Point positionShouldBe(1, 0);
	Point positionReal(player.getPosition());

	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_placeBombAndWaitExactTheBombLifeTime_bombCountIs0()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	const GameState &game = m_gameEngine->getGameState();
	InputState input;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	vector<const BombState*> bombs = game.getAllChangedBombs();
	const BombState &bomb = *(bombs.front());
	double bombLifeTime = bomb.getLifeTime();
	m_gameEngine->updateGameState(m_inputStates, bombLifeTime);
	m_gameEngine->updateGameState(m_inputStates, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)0, game.getBombCount());
}

void GameEngineImplTest::updateGameState_placeBombAndStayAtPlace_playerDoesntMove()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	const GameState &game = m_gameEngine->getGameState();
	InputState input;

	input.setSpaceKeyPressed();
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	m_gameEngine->updateGameState(m_inputStates, 1);

	const PlayerState &player = game.getFirstPlayerState();

	CPPUNIT_ASSERT(Point(0, 0).fuzzyEqual(player.getPosition(), 0.05));
}

void GameEngineImplTest::updateGameState_placeBombMoveAwayAndTryToMoveThroughBomb_playerStaysBesideBomb()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	InputState input;

	input.setSpaceKeyPressed();
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField);

	CPPUNIT_ASSERT(Point(1, 0).fuzzyEqual(player.getPosition(), 0.05));
}

void GameEngineImplTest::increaseMaxBombCount_placeTwoBombsAtTheSameTime_BombCountIs2()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	GameState &game = m_gameEngine->getGameState();
	PlayerState &player = game.getFirstPlayerState();
	InputState input;

	player.increaseMaxBombs();
	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, (1.5*m_defaultTimeForOneField));
	input.setUpKeyNotPressed();
	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);

	CPPUNIT_ASSERT_EQUAL((size_t)2, game.getBombCount());
}

void GameEngineImplTest::increaseMaxBombCount_placeThreeBombsAtTheSameTime_BombCountIs2()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	GameState &game = m_gameEngine->getGameState();
	PlayerState &player = game.getFirstPlayerState();
	InputState input;

	player.increaseMaxBombs();
	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, (1.5*m_defaultTimeForOneField));
	input.setUpKeyNotPressed();
	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, (1.5*m_defaultTimeForOneField));
	input.setUpKeyNotPressed();
	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);

	CPPUNIT_ASSERT_EQUAL((size_t)2, game.getBombCount());
}

void GameEngineImplTest::setBombsLifeTimeToZero_placeTwoBombsOneExplodes_LifeTimeOfSecondBombIs0()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	GameState &game = m_gameEngine->getGameState();
	PlayerState &player = game.getFirstPlayerState();
	InputState input;

	player.increaseMaxBombs();
	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, (m_defaultTimeForOneField));
	input.setUpKeyNotPressed();
	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 2.5);
	m_gameEngine->updateGameState(m_inputStates, 0);
	vector<const BombState*> bombs = game.getAllChangedBombs();
	const BombState &bomb = *(bombs.front());

	CPPUNIT_ASSERT_EQUAL((double)0, bomb.getLifeTime());
}

void GameEngineImplTest::getPlayerPosition_Create4x4LevelWithPlayerPosition2And2_PlayerPosition2And2()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 2);
	createGameEngine(level, 1, 0);
	const PlayerState *player;
	const Point point(2,2);

	const GameState &game = m_gameEngine->getGameState();
	player = game.getAllPlayers().front();

	CPPUNIT_ASSERT_EQUAL((const Point)point, player->getPosition());
}

void GameEngineImplTest::getPlayerCount_Create4x4LevelWith2Player_PlayerCountIs2()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	createGameEngine(level, 2, 0);

	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)2, game.getPlayerCount());
}

void GameEngineImplTest::updateGameState_onePlayerDestroysTheOtherOne_playerCountIs1()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 1);
	createGameEngine(level, 2, 0);
	InputState input;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1.1*m_defaultTimeForOneField);
	input.setUpKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 5);
	m_gameEngine->updateGameState(m_inputStates, 0);

	const GameState &game = m_gameEngine->getGameState();
	CPPUNIT_ASSERT_EQUAL((size_t)1, game.getPlayerCount());
}

void GameEngineImplTest::getPosition_getpositionaftercollisionwithotherplayer()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 1);
	createGameEngine(level, 2, 0);

	GameState &game = m_gameEngine->getGameState();
	PlayerState &firstPlayer = game.getFirstPlayerState();
	PlayerState &secondPlayer = game.getSecondPlayerState();
	Point pointTwo(2, 1);
	Point pointOne(0, 1);
	firstPlayer.setPosition(pointOne);
	secondPlayer.setPosition(pointTwo);
	InputState input;

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, m_defaultTimeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0.1);

	input.setLeftKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1);
	input.setLeftKeyNotPressed();
	m_gameEngine->updateGameState(m_inputStates, 0.1);
	Point pointPositionEquals = secondPlayer.getPosition();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, pointPositionEquals.getX(), 0.05);
}

void GameEngineImplTest::createGameEngine(const LevelDefinition &level, unsigned int humanPlayerCount, unsigned int computerEnemyCount)
{
	if (m_gameEngine != 0)
		delete m_gameEngine;
	m_inputStates.clear();

	m_gameEngine = new GameEngineImpl(level, humanPlayerCount, computerEnemyCount);
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &firstPlayer = gameState.getFirstPlayerState();
	vector<unsigned int> allPlayerIDs = gameState.getAllNotDestroyedPlayerIDs();
	m_firstPlayerID = firstPlayer.getId();

	if (humanPlayerCount > 1)
	{
		const PlayerState &secondPlayer = gameState.getSecondPlayerState();
		m_secondPlayerID = secondPlayer.getId();
	}

	for (vector<unsigned int>::const_iterator i = allPlayerIDs.begin(); i != allPlayerIDs.end(); ++i)
		m_inputStates.insert(pair<unsigned int, InputState>(*i, InputState()));

	m_defaultTimeForOneField = 1/firstPlayer.getSpeed();
}

void GameEngineImplTest::setFirstPlayerInput(const InputState &input)
{
	m_inputStates[m_firstPlayerID] = input;
}

void GameEngineImplTest::setSecondPlayerInput(const InputState &input)
{
	m_inputStates[m_secondPlayerID] = input;
}


void GameEngineImplTest::setUp()
{
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
}

void GameEngineImplTest::tearDown()
{
	m_inputStates.clear();
	delete m_gameEngine;
	m_gameEngine = 0;
}


void GameEngineImplTest::addPowerUp_powerUpCountIs1PlayerWalksOnPowerUp_powerUpCountIs0()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;
	m_gameEngine->addPowerUpOfTypeAtPosition(PowerUpTypeMaxBomb, Point(1,0));
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, (m_defaultTimeForOneField));
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	m_gameEngine->updateGameState(m_inputStates, 0);

	GameState &game = m_gameEngine->getGameState();
	CPPUNIT_ASSERT_EQUAL((size_t)0, game.getPowerUpCount());
}

void GameEngineImplTest::updateGameState_AddTwoPowerUpsOneInRangeOfBombAndLetBombExplode_powerUpCountIs1()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	createGameEngine(level, 1, 0);
	InputState input;
	GameState &game = m_gameEngine->getGameState();

	m_gameEngine->addPowerUpOfTypeAtPosition(PowerUpTypeMaxBomb, Point(1,0));
	m_gameEngine->addPowerUpOfTypeAtPosition(PowerUpTypeMaxVelocity, Point(2,2));
	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	m_gameEngine->updateGameState(m_inputStates, 3.1);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);

	CPPUNIT_ASSERT_EQUAL((size_t)1, game.getPowerUpCount());
}
