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

void GameEngineImplTest::updateGameState_twoBombsPlacedAndOneDestroyed_bombCountIs1()
{
	InputState input;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 3.1);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyPressed();
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
	createGameEngine(level, 1);
	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL(level.getLevelHeight(), game.getHeight());
}

void GameEngineImplTest::getWidth_WidthOfLevelDefinition_WidthOfGamestate()
{
	LevelDefinition level;
	createGameEngine(level, 1);
	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL(level.getLevelWidth(), game.getWidth());
}

void GameEngineImplTest::updateGameState_tryToMoveThroughRightBorder_playerPositionIsAtRightBorder()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
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
	createGameEngine(level, 1);
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
	createGameEngine(level, 1);
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
	createGameEngine(level, 1);
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
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 3, 3);
	createGameEngine(level, 1);

	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)2, game.getWallCount());
}

void GameEngineImplTest::getWallPosition_Create4x4LevelWithWallPosition2And2_WallPosition2And2()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 2, 2);
	createGameEngine(level, 1);
	const WallState *wall;
	const Point point(2,2);

	const GameState &game = m_gameEngine->getGameState();
	wall = game.getAllChangedWalls().front();

	CPPUNIT_ASSERT_EQUAL((const Point)point, wall->getPosition());
}

void GameEngineImplTest::getWallType_Create4x4LevelWallWithWallType_WallTypeIsLoose()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 2, 2);
	createGameEngine(level, 1);
	const WallState *wall;

	const GameState &game = m_gameEngine->getGameState();
	wall = game.getAllChangedWalls().front();

	CPPUNIT_ASSERT_EQUAL(WallState::WallTypeLoose, wall->getWallType());
}

void GameEngineImplTest::updateGameState_halfTheTimeOfTheMovementToTheNextGridFieldButtonPressed_playerReachesGridPoint()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
	InputState input;
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	const double timeForField = 1/player.getMaximumSpeed();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForField/2);

	Point positionShouldBe(1, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void GameEngineImplTest::updateGameState_playerVerticalBetweenTwoFieldsAndUpPressed_playerKeepsDirection()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
	InputState input;
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1/(2*player.getMaximumSpeed()));
	input.setRightKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1/(2*player.getMaximumSpeed()));

	Point positionShouldBe(1, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionReal.fuzzyEqual(positionShouldBe, 0.05));
}

void GameEngineImplTest::getWallCount_Create4x4LevelWith2WallsOneWallInRangeOfBombAndBombExplodes_WallCount1()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 1, 0);
	createGameEngine(level, 1);
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
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 0);
	createGameEngine(level, 1);
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
	createGameEngine(level, 1);
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
	createGameEngine(level, 1);
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
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	createGameEngine(level, 1);
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
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 1, 1);
	createGameEngine(level, 1);
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
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 3, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 3, 4);
	createGameEngine(level, 1);
	InputState input;
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &playerState = gameState.getFirstPlayerState();
	const double timeForOneField = 1/playerState.getMaximumSpeed();


	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1.5*timeForOneField);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 20*timeForOneField);
	input.setUpKeyNotPressed();
	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 5.5*timeForOneField);
	input.setDownKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);

	Point newPosition = playerState.getPosition();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, newPosition.getX(), 0.05);
}


void GameEngineImplTest::updateGameState_moveTowardsWallAndAgainAway_playerPositionIsCorrect()
{
	LevelDefinition level(15, 10);
	createGameEngine(level, 1);
	InputState input;
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &playerState = gameState.getFirstPlayerState();
	const double timeForOneField = 1/playerState.getMaximumSpeed();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setUpKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField*2);
	input.setLeftKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField*2);
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);

	Point realPosition = playerState.getPosition();
	Point positionShouldBe(1, 1);
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(realPosition, 0.05));
}

void GameEngineImplTest::updateGameState_pressRightAndThenUp_playerKeepsDirection()
{
	InputState input;
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &playerState = gameState.getFirstPlayerState();
	const double timeForOneField = 1/playerState.getMaximumSpeed();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);
	input.setRightKeyNotPressed();
	input.setUpKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);

	Point positionShouldBe(2, 0);
	Point positionReal(playerState.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_pressLeftAndThenDown_playerKeepsDirection()
{
	InputState input;
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &playerState = gameState.getFirstPlayerState();
	const double timeForOneField = 1/playerState.getMaximumSpeed();
	playerState.setPosition(Point(5, 1));

	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);
	input.setLeftKeyNotPressed();
	input.setDownKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);

	Point positionShouldBe(3, 1);
	Point positionReal(playerState.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_pressUpAndThenRight_playerKeepsDirection()
{
	InputState input;
	const GameState &gameState = m_gameEngine->getGameState();
	const PlayerState &playerState = gameState.getFirstPlayerState();
	const double timeForOneField = 1/playerState.getMaximumSpeed();

	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);
	input.setUpKeyNotPressed();
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);

	Point positionShouldBe(0, 2);
	Point positionReal(playerState.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGamestate_pressDownAndThenLeft_playerKeepsDirection()
{
	InputState input;
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &playerState = gameState.getFirstPlayerState();
	const double timeForOneField = 1/playerState.getMaximumSpeed();
	playerState.setPosition(Point(3, 5));

	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);
	input.setDownKeyNotPressed();
	input.setLeftKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);

	Point positionShouldBe(3, 3);
	Point positionReal(playerState.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_movementOfSecondPlayer_positionOfSecondPlayerIsCorrect()
{
	InputState input;
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createGameEngine(level, 2);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &firstPlayer = gameState.getFirstPlayerState();
	PlayerState &secondPlayer = gameState.getSecondPlayerState();
	const double timeForOneField = 1/secondPlayer.getMaximumSpeed();
	firstPlayer.setPosition(Point(0, 0));
	secondPlayer.setPosition(Point(0, 1));

	input.setRightKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setRightKeyNotPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);

	Point positionShouldBe(1, 1);
	Point positionReal(secondPlayer.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_movementOfSecondPlayer_firstPlayerDoesntMove()
{
	InputState input;
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	createGameEngine(level, 2);
	GameState &gameState = m_gameEngine->getGameState();
	PlayerState &firstPlayer = gameState.getFirstPlayerState();
	PlayerState &secondPlayer = gameState.getSecondPlayerState();
	const double timeForOneField = 1/secondPlayer.getMaximumSpeed();
	firstPlayer.setPosition(Point(0, 0));
	secondPlayer.setPosition(Point(0, 1));

	input.setRightKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setRightKeyNotPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);

	Point positionShouldBe(0, 0);
	Point positionReal(firstPlayer.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayRightToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	InputState input;
	double halfTimeToReachGridPoint = 1/(2*player.getMaximumSpeed());

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, halfTimeToReachGridPoint);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(halfTimeToReachGridPoint, m_gameEngine->getTimeTillOnePlayerReachesGridPoint(), 0.0001);
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayLeftToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	InputState input;
	double halfTimeToReachGridPoint = 1/(2*player.getMaximumSpeed());

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, halfTimeToReachGridPoint*10);
	input.setRightKeyNotPressed();
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, halfTimeToReachGridPoint);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(halfTimeToReachGridPoint, m_gameEngine->getTimeTillOnePlayerReachesGridPoint(), 0.05);
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayUpToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	InputState input;
	double halfTimeToReachGridPoint = 1/(2*player.getMaximumSpeed());

	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, halfTimeToReachGridPoint);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(halfTimeToReachGridPoint, m_gameEngine->getTimeTillOnePlayerReachesGridPoint(), 0.0001);
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayDownToGridPoint_halfTimeToMoveBetweenTwoGridPoints()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	InputState input;
	double halfTimeToReachGridPoint = 1/(2*player.getMaximumSpeed());

	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, halfTimeToReachGridPoint*10);
	input.setUpKeyNotPressed();
	input.setDownKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, halfTimeToReachGridPoint);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(halfTimeToReachGridPoint, m_gameEngine->getTimeTillOnePlayerReachesGridPoint(), 0.05);
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerStaysOnGridPoint_veryLong()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);

	m_gameEngine->updateGameState(m_inputStates, 10);

	CPPUNIT_ASSERT(m_gameEngine->getTimeTillOnePlayerReachesGridPoint() > 100000);
}

void GameEngineImplTest::getTimeTillOnePlayerReachesGridPoint_playerIsMovingButDirectOnGridField_timeToReachNextGridField()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
	InputState input;
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);

	double time = m_gameEngine->getTimeTillOnePlayerReachesGridPoint();
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	double timeShouldBe = 1/player.getMaximumSpeed();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(timeShouldBe, time, 0.0001);
}

void GameEngineImplTest::updateGameState_keyPressedHalfWayToGridFieldAndEnoughTimeToReachIt_playerPositionIsGridField()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	InputState input;
	double timeForOneField = 1/player.getMaximumSpeed();

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);

	Point positionShouldBe(1, 0);
	Point positionReal(player.getPosition());
	CPPUNIT_ASSERT(positionShouldBe.fuzzyEqual(positionReal, 0.05));
}

void GameEngineImplTest::updateGameState_placeBombAndWaitExactTheBombLifeTime_bombCountIs0()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
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
	createGameEngine(level, 1);
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
	createGameEngine(level, 1);
	const GameState &game = m_gameEngine->getGameState();
	const PlayerState &player = game.getFirstPlayerState();
	double timeForOneField = 1/player.getMaximumSpeed();
	InputState input;

	input.setSpaceKeyPressed();
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);
	input.setLeftKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField);

	CPPUNIT_ASSERT(Point(1, 0).fuzzyEqual(player.getPosition(), 0.05));
}

void GameEngineImplTest::increaseMaxBombCount_placeTwoBombsAtTheSameTime_BombCountIs2()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
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
	m_gameEngine->updateGameState(m_inputStates, (1.5/player.getMaximumSpeed()));
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
	createGameEngine(level, 1);
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
	m_gameEngine->updateGameState(m_inputStates, (1.5/player.getMaximumSpeed()));
	input.setUpKeyNotPressed();
	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, (1.5/player.getMaximumSpeed()));
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
	createGameEngine(level, 1);
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
	m_gameEngine->updateGameState(m_inputStates, (1.0/player.getMaximumSpeed()));
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
	createGameEngine(level, 1);
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
	createGameEngine(level, 2);

	const GameState &game = m_gameEngine->getGameState();

	CPPUNIT_ASSERT_EQUAL((size_t)2, game.getPlayerCount());
}

void GameEngineImplTest::getPlayerCount_Create4x4LevelWith2PlayerOnePlayerDestroyed_PlayerCountIs1()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 1);
	createGameEngine(level, 2);

	const GameState &game = m_gameEngine->getGameState();
	InputState input;

	input.setSpaceKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	input.setSpaceKeyNotPressed();
	setFirstPlayerInput(input);
	input.setUpKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1);
	input.setUpKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 2.1);
	m_gameEngine->updateGameState(m_inputStates, 0);


	CPPUNIT_ASSERT_EQUAL((size_t)1, game.getPlayerCount());
}

void GameEngineImplTest::getPosition_getpositionaftercollisionwithotherplayer()
{
	LevelDefinition level(4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 1);
	createGameEngine(level, 2);

	GameState &game = m_gameEngine->getGameState();
	PlayerState &firstPlayer = game.getFirstPlayerState();
	PlayerState &secondPlayer = game.getSecondPlayerState();

	const double timeForOneField = 1/firstPlayer.getMaximumSpeed();
	Point pointTwo(2,1);
	Point pointOne(0,1);


	firstPlayer.setPosition(pointOne);
	secondPlayer.setPosition(pointTwo);
	InputState input;

	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, timeForOneField/2);
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0.1);

	input.setLeftKeyPressed();
	setSecondPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 1);
	input.setLeftKeyNotPressed();
	m_gameEngine->updateGameState(m_inputStates, 0.1);
	Point pointPositionEquals = secondPlayer.getPosition();
	double x = pointPositionEquals.getX();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(x,2.0,0.05);
}

void GameEngineImplTest::createGameEngine(const LevelDefinition &level, unsigned int playerCount)
{
	if (m_gameEngine != 0)
		delete m_gameEngine;
	m_inputStates.clear();

	m_gameEngine = new GameEngineImpl(level, playerCount);
	vector<unsigned int> playerIDs = m_gameEngine->getAllPossiblePlayerIDs();
	m_firstPlayerID = playerIDs[0];

	if (playerCount > 1)
		m_secondPlayerID = playerIDs[1];

	for (vector<unsigned int>::const_iterator i = playerIDs.begin(); i != playerIDs.end(); ++i)
		m_inputStates.insert(pair<unsigned int, InputState>(*i, InputState()));
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
	createGameEngine(LevelDefinition(), 1);
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
	createGameEngine(level, 1);
	GameState &game = m_gameEngine->getGameState();
	InputState input;
	PlayerState &player = game.getFirstPlayerState();

	m_gameEngine->addPowerUpOfTypeAtPosition(PowerUpTypeMaxBomb, Point(1,0));
	input.setRightKeyPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, (1/player.getMaximumSpeed()));
	input.setRightKeyNotPressed();
	setFirstPlayerInput(input);
	m_gameEngine->updateGameState(m_inputStates, 0);
	m_gameEngine->updateGameState(m_inputStates, 0);

	size_t result = game.getPowerUpCount();

	CPPUNIT_ASSERT_EQUAL((size_t)0, result);
}

void GameEngineImplTest::updateGameState_AddTwoPowerUpsOneInRangeOfBombAndLetBombExplode_powerUpCountIs1()
{
	LevelDefinition level(4, 4);
	createGameEngine(level, 1);
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
