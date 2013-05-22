#include "gameengineimpltest.h"
#include "gameengineimpl.h"

using namespace GameEngine;
using namespace Common;

void GameEngineImplTest::updateGameState_UpKeyPressed_PlayerDirectionUp()
{
    GameEngineImpl gameEngine;
    InputState input;
    GameState game;
    PlayerState player;

    input.setUpKeyPressed();
    gameEngine.updateGameState(input,0);
    game = gameEngine.getGameState();
    player = game.getPlayerState();

    CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionUp, player.getDirection());
}

void GameEngineImplTest::updateGameState_DownKeyPressed_PlayerDirectionDown()
{
    GameEngineImpl gameEngine;
    InputState input;
    GameState game;
    PlayerState player;

    input.setDownKeyPressed();
    gameEngine.updateGameState(input,0);
    game=gameEngine.getGameState();
    player=game.getPlayerState();

    CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionDown, player.getDirection());
}

void GameEngineImplTest::updateGameState_LeftKeyPressed_PlayerDirectionLeft()
{
    GameEngineImpl gameEngine;
    InputState input;
    GameState game;
    PlayerState player;

    input.setLeftKeyPressed();
    gameEngine.updateGameState(input,0);
    game=gameEngine.getGameState();
    player=game.getPlayerState();

    CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionLeft, player.getDirection());
}

void GameEngineImplTest::updateGameState_RightKeyPressed_PlayerDirectionRight()
{
    GameEngineImpl gameEngine;
    InputState input;
    GameState game;
    PlayerState player;

    input.setRightKeyPressed();
    gameEngine.updateGameState(input,0);
    game=gameEngine.getGameState();
    player=game.getPlayerState();

    CPPUNIT_ASSERT_EQUAL(PlayerState::PlayerDirectionRight, player.getDirection());
}
