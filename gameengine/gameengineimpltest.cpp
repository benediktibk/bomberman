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
