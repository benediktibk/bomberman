#include "gameengineimpltest.h"
#include "gameengineimpl.h"


using namespace GameEngine;
using namespace Common;

void GameEngineImplTest::updateGameState_UpKeyPressed_PlayerDirectionUp()
{
	LevelDefinition level;
	GameEngineImpl gameEngine(level);
	InputState input;

	input.setUpKeyPressed();
	gameEngine.updateGameState(input,0);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionUp, player.getDirection());
}

void GameEngineImplTest::updateGameState_DownKeyPressed_PlayerDirectionDown()
{
	LevelDefinition level;
	GameEngineImpl gameEngine(level);
	InputState input;

	input.setDownKeyPressed();
	gameEngine.updateGameState(input,0);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionDown, player.getDirection());
}

void GameEngineImplTest::updateGameState_LeftKeyPressed_PlayerDirectionLeft()
{
	LevelDefinition level;
	GameEngineImpl gameEngine(level);
	InputState input;

	input.setLeftKeyPressed();
	gameEngine.updateGameState(input,0);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionLeft, player.getDirection());
}

void GameEngineImplTest::updateGameState_RightKeyPressed_PlayerDirectionRight()
{
	LevelDefinition level;
	GameEngineImpl gameEngine(level);
	InputState input;

	input.setRightKeyPressed();
	gameEngine.updateGameState(input,0);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionRight, player.getDirection());
}

void GameEngineImplTest::updateGameState_oneBombPlaced_bombPositionIsSameAsPlayerPosition()
{
	LevelDefinition level;
	GameEngineImpl gameEngine(level);
	InputState input;
	const BombState *bomb;

	input.setSpaceKeyPressed();
	gameEngine.updateGameState(input,0);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();
	bomb = game.getAllChangedBombs().front();

	CPPUNIT_ASSERT(player.getPosition().fuzzyEqual(bomb->getPosition(), 0.001));
}

void GameEngineImplTest::updateGameState_oneBombPlaced_bombLifeTimeIs2()
{
	LevelDefinition level;
	GameEngineImpl gameEngine(level);
	InputState input;
	const BombState *bomb;

	input.setSpaceKeyPressed();
	gameEngine.updateGameState(input,0);
	input.setSpaceKeyNotPressed();
	gameEngine.updateGameState(input,1);
	const GameState &game = gameEngine.getGameState();
	bomb = game.getAllChangedBombs().front();

	CPPUNIT_ASSERT_EQUAL((double)2, bomb->getLifeTime());
}

void GameEngineImplTest::updateGameState_twoBombsPlacedAndOneDestroyed_bombCountIs1()
{
	LevelDefinition level;
	GameEngineImpl gameEngine(level);
	InputState input;

	input.setSpaceKeyPressed();
	gameEngine.updateGameState(input, 0);
	gameEngine.updateGameState(input, 3.1);
	input.setSpaceKeyNotPressed();
	gameEngine.updateGameState(input, 0);
	const GameState &game = gameEngine.getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)1, game.getBombCount());
}

void GameEngineImplTest::getHeight_HeightOfLevelDefinition_HeightOfGamestate()
{
	LevelDefinition level;
	GameEngineImpl gameEngine(level);
	const GameState &game = gameEngine.getGameState();

	CPPUNIT_ASSERT_EQUAL(level.getLevelHeight(), game.getGameStateHeight());
}

void GameEngineImplTest::getWidth_WidthOfLevelDefinition_WidthOfGamestate()
{
	LevelDefinition level;
	GameEngineImpl gameEngine(level);
	const GameState &game = gameEngine.getGameState();

	CPPUNIT_ASSERT_EQUAL(level.getLevelWidth(), game.getGameStateWidth());
}

void GameEngineImplTest::updateGameState_tryToMoveThroughRightBorder_playerPositionIsAtRightBorder()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	InputState inputState;
	inputState.setRightKeyPressed();

	gameEngine.updateGameState(inputState, 10);

	const GameState &game = gameEngine.getGameState();
	const PlayerState &playerState = game.getPlayerState();
	Point positionShouldBe(3, 0);
	Point positionReal(playerState.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_tryToMoveThroughUpperBorder_playerPositionIsAtUpperBorder()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	InputState inputState;
	inputState.setUpKeyPressed();

	gameEngine.updateGameState(inputState, 10);

	const GameState &game = gameEngine.getGameState();
	const PlayerState &playerState = game.getPlayerState();
	Point positionShouldBe(0, 3);
	Point positionReal(playerState.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_tryToMoveThroughLowerBorder_playerPositionIsAtLowerBorder()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	InputState inputState;
	inputState.setDownKeyPressed();

	gameEngine.updateGameState(inputState, 10);

	const GameState &game = gameEngine.getGameState();
	const PlayerState &playerState = game.getPlayerState();
	Point positionShouldBe(0, 0);
	Point positionReal(playerState.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_tryToMoveThroughLeftBorder_playerPositionIsAtLeftBorder()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	InputState inputState;
	inputState.setLeftKeyPressed();

	gameEngine.updateGameState(inputState, 10);

	const GameState &game = gameEngine.getGameState();
	const PlayerState &playerState = game.getPlayerState();
	Point positionShouldBe(0, 0);
	Point positionReal(playerState.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::getWallCount_Create4x4LevelWith2Wall_WallCount2()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall,1,3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall,3,3);
	GameEngineImpl gameEngine(level);

	const GameState &game = gameEngine.getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)2, game.getWallCount());
}

void GameEngineImplTest::getWallPosition_Create4x4LevelWithWallPosition2And2_WallPosition2And2()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall,2,2);
	GameEngineImpl gameEngine(level);
	const WallState *wall;
	const Point point(2,2);

	const GameState &game = gameEngine.getGameState();
	wall = game.getAllChangedWalls().front();

	CPPUNIT_ASSERT_EQUAL((const Point)point, wall->getPosition());
}

void GameEngineImplTest::getWallType_Create4x4LevelWallWithWallType_WallTypeIsLoose()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 2, 2);
	GameEngineImpl gameEngine(level);
	const WallState *wall;

	const GameState &game = gameEngine.getGameState();
	wall = game.getAllChangedWalls().front();

	CPPUNIT_ASSERT_EQUAL(WallState::WallTypeLoose, wall->getWallType());
}

void GameEngineImplTest::updateGameState_halfTheTimeOfTheMovementToTheNextGridFieldButtonPressed_playerStaysInBetween()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	InputState inputState;
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();

	inputState.setRightKeyPressed();
	gameEngine.updateGameState(inputState, 1/(2*player.getSpeed()));
	inputState.setRightKeyNotPressed();
	gameEngine.updateGameState(inputState, 1/(2*player.getSpeed()));

	Point positionShouldBe(0.5, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void GameEngineImplTest::updateGameState_playerVerticalBetweenTwoFieldsAndUpPressed_playerDoesntMove()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	InputState inputState;
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();

	inputState.setRightKeyPressed();
	gameEngine.updateGameState(inputState, 1/(2*player.getSpeed()));
	inputState.setRightKeyNotPressed();
	inputState.setUpKeyPressed();
	gameEngine.updateGameState(inputState, 1/(2*player.getSpeed()));

	Point positionShouldBe(0.5, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}
