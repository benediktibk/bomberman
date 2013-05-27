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

void GameEngineImplTest::updateGameState_SpaceKeyPressed_BombPlaced()
{
    GameEngineImpl gameEngine;
    InputState input;
    GameState game;
    PlayerState player;
    BombState bomb;
    BombState setBomb;

    input.setSpaceKeyPressed();
    gameEngine.updateGameState(input,0);
    game=gameEngine.getGameState();
    player=game.getPlayerState();
    bomb=game.getAllBombs().front();
    setBomb.setPosition(player.getPosition());

    CPPUNIT_ASSERT_EQUAL(setBomb.getPosition(), bomb.getPosition());
}
