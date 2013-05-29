#include "gameengineimpltest.h"
#include "gameengineimpl.h"


using namespace GameEngine;
using namespace Common;

void GameEngineImplTest::updateGameState_UpKeyPressed_PlayerDirectionUp()
{
	GameEngineImpl gameEngine;
	InputState input;

	input.setUpKeyPressed();
	gameEngine.updateGameState(input,0);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionUp, player.getDirection());
}

void GameEngineImplTest::updateGameState_DownKeyPressed_PlayerDirectionDown()
{
	GameEngineImpl gameEngine;
	InputState input;

	input.setDownKeyPressed();
	gameEngine.updateGameState(input,0);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionDown, player.getDirection());
}

void GameEngineImplTest::updateGameState_LeftKeyPressed_PlayerDirectionLeft()
{
	GameEngineImpl gameEngine;
	InputState input;

	input.setLeftKeyPressed();
	gameEngine.updateGameState(input,0);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionLeft, player.getDirection());
}

void GameEngineImplTest::updateGameState_RightKeyPressed_PlayerDirectionRight()
{
	GameEngineImpl gameEngine;
	InputState input;

	input.setRightKeyPressed();
	gameEngine.updateGameState(input,0);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();

	CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionRight, player.getDirection());
}

void GameEngineImplTest::updateGameState_SpaceKeyPressed_BombPlaced_testPosition()
{
	GameEngineImpl gameEngine;
	InputState input;
	const BombState *bomb;

	input.setSpaceKeyPressed();
	gameEngine.updateGameState(input,0);
	const GameState &game = gameEngine.getGameState();
	const PlayerState &player = game.getPlayerState();
	bomb = game.getAllChangedBombs().front();

	CPPUNIT_ASSERT_EQUAL(player.getPosition(), bomb->getPosition());
}

void GameEngineImplTest::updateGameState_SpaceKeyPressed_BombPlaced_testBombLifeTime_resultIs2()
{
    GameEngineImpl gameEngine;
    InputState input;
    const BombState *bomb;

    input.setSpaceKeyPressed();
    gameEngine.updateGameState(input,0);
    gameEngine.updateGameState(input,1);
    const GameState &game = gameEngine.getGameState();
    bomb = game.getAllChangedBombs().front();

    CPPUNIT_ASSERT_EQUAL((double)2, bomb->getLifeTime());
}

void GameEngineImplTest::updateGameState_SpaceKeyPressed_towBombsPlaced_oneBombDelete_testBombCount_resultIs1()
{
    GameEngineImpl gameEngine;
    InputState input;

    input.setSpaceKeyPressed();
    gameEngine.updateGameState(input,0);
    gameEngine.updateGameState(input,3.1);
    const GameState &game = gameEngine.getGameState();

    CPPUNIT_ASSERT_EQUAL((size_t)1, game.getBombCount());
}
