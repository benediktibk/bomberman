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
	gameEngine.updateGameState(input, 1);
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

void GameEngineImplTest::updateGameState_halfTheTimeOfTheMovementToTheNextGridFieldButtonPressed_playerReachesGridPoint()
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

	Point positionShouldBe(1, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void GameEngineImplTest::updateGameState_playerVerticalBetweenTwoFieldsAndUpPressed_playerKeepsDirection()
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

	Point positionShouldBe(1, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void GameEngineImplTest::getWallCount_Create4x4LevelWith2WallsOneWallInRangeOfBombAndBombExplodes_WallCount1()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall,1,3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall,1,0);
	GameEngineImpl gameEngine(level);
	InputState input;

	input.setSpaceKeyPressed();
	gameEngine.updateGameState(input, 0);
	gameEngine.updateGameState(input, 3.1);
	input.setSpaceKeyNotPressed();
	gameEngine.updateGameState(input, 0);

	const GameState &game = gameEngine.getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)1, game.getWallCount());
}

void GameEngineImplTest::updateGameState_Create4x4LevelWithSolidWallAndLetBombExplode_wallCountIs1()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 0);
	GameEngineImpl gameEngine(level);
	InputState input;

	input.setSpaceKeyPressed();
	gameEngine.updateGameState(input, 0);
	input.setSpaceKeyNotPressed();
	gameEngine.updateGameState(input, 3.1);
	gameEngine.updateGameState(input, 0);

	const GameState &game = gameEngine.getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)1, game.getWallCount());
}

void GameEngineImplTest::updateGameState_placeBombAndWaitTillItExploded_bombCountIs0()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	InputState input;

	input.setSpaceKeyPressed();
	gameEngine.updateGameState(input, 0);
	input.setSpaceKeyNotPressed();
	gameEngine.updateGameState(input, 3.1);
	gameEngine.updateGameState(input, 0);

	const GameState &game = gameEngine.getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)0, game.getBombCount());
}

void GameEngineImplTest::updateGameState_playerSurroundedByWallsAndTriesToMoveUp_playerMovedUp()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	GameEngineImpl gameEngine(level);
	InputState input;
	const GameState &gameState = gameEngine.getGameState();
	const PlayerState &playerState = gameState.getPlayerState();
	Point initialPosition = playerState.getPosition();

	input.setUpKeyPressed();
	gameEngine.updateGameState(input, 10);

	Point newPosition = playerState.getPosition();
	CPPUNIT_ASSERT(newPosition.getY() > initialPosition.getY());
}

void GameEngineImplTest::updateGameState_playerSurroundedByWallsAndTriesToMoveRight_playerMovedRight()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	GameEngineImpl gameEngine(level);
	InputState input;
	const GameState &gameState = gameEngine.getGameState();
	const PlayerState &playerState = gameState.getPlayerState();
	Point initialPosition = playerState.getPosition();

	input.setRightKeyPressed();
	gameEngine.updateGameState(input, 10);

	Point newPosition = playerState.getPosition();
	CPPUNIT_ASSERT(newPosition.getX() > initialPosition.getX());
}

void GameEngineImplTest::updateGameState_moveToUpperBorderAndBackAndTryToGetRightBetweenTwoWalls_playerMovedRight()
{
	LevelDefinition level(15, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 3, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 3, 4);
	GameEngineImpl gameEngine(level);
	InputState input;
	const GameState &gameState = gameEngine.getGameState();
	const PlayerState &playerState = gameState.getPlayerState();
	const double timeForOneField = 1/playerState.getSpeed();


	input.setRightKeyPressed();
	gameEngine.updateGameState(input, 1.5*timeForOneField);
	input.setRightKeyNotPressed();
	gameEngine.updateGameState(input, timeForOneField);
	input.setUpKeyPressed();
	gameEngine.updateGameState(input, 20*timeForOneField);
	input.setUpKeyNotPressed();
	input.setDownKeyPressed();
	gameEngine.updateGameState(input, 5.5*timeForOneField);
	input.setDownKeyNotPressed();
	gameEngine.updateGameState(input, timeForOneField);
	input.setRightKeyPressed();
	gameEngine.updateGameState(input, timeForOneField);

	Point newPosition = playerState.getPosition();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, newPosition.getX(), 0.05);
}

void GameEngineImplTest::getTimeTillPlayerReachesGridPoint_playerMovedHalfWayRightToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();
	InputState input;
	double halfTimeToReachGridPoint = 1/(2*player.getSpeed());

	input.setRightKeyPressed();
	gameEngine.updateGameState(input, halfTimeToReachGridPoint);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(halfTimeToReachGridPoint, gameEngine.getTimeTillPlayerReachesGridPoint(), 0.0001);
}

void GameEngineImplTest::getTimeTillPlayerReachesGridPoint_playerMovedHalfWayLeftToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();
	InputState input;
	double halfTimeToReachGridPoint = 1/(2*player.getSpeed());

	input.setRightKeyPressed();
	gameEngine.updateGameState(input, halfTimeToReachGridPoint*10);
	input.setRightKeyNotPressed();
	input.setLeftKeyPressed();
	gameEngine.updateGameState(input, halfTimeToReachGridPoint);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(halfTimeToReachGridPoint, gameEngine.getTimeTillPlayerReachesGridPoint(), 0.05);
}

void GameEngineImplTest::getTimeTillPlayerReachesGridPoint_playerMovedHalfWayUpToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();
	InputState input;
	double halfTimeToReachGridPoint = 1/(2*player.getSpeed());

	input.setUpKeyPressed();
	gameEngine.updateGameState(input, halfTimeToReachGridPoint);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(halfTimeToReachGridPoint, gameEngine.getTimeTillPlayerReachesGridPoint(), 0.0001);
}

void GameEngineImplTest::getTimeTillPlayerReachesGridPoint_playerMovedHalfWayDownToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();
	InputState input;
	double halfTimeToReachGridPoint = 1/(2*player.getSpeed());

	input.setUpKeyPressed();
	gameEngine.updateGameState(input, halfTimeToReachGridPoint*10);
	input.setUpKeyNotPressed();
	input.setDownKeyPressed();
	gameEngine.updateGameState(input, halfTimeToReachGridPoint);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(halfTimeToReachGridPoint, gameEngine.getTimeTillPlayerReachesGridPoint(), 0.05);
}

void GameEngineImplTest::getTimeTillPlayerReachesGridPoint_playerStaysOnGridPoint_0()
{
	LevelDefinition level(4, 4);
	GameEngineImpl gameEngine(level);;
	InputState input;

	gameEngine.updateGameState(input, 10);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, gameEngine.getTimeTillPlayerReachesGridPoint(), 0.05);
}
