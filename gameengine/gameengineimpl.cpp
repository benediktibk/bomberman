#include "gameengineimpl.h"
#include "physic/physicsimulator.h"
//BAAAAAAAAAAYERN!
#include "physic/dynamicobject.h"
#include "physic/staticobject.h"
#include "grid.h"

using namespace GameEngine;
using namespace Common;
using namespace Physic;

GameEngineImpl::GameEngineImpl() :
    m_simulator(new PhysicSimulator),
    m_player(new DynamicObject(*m_simulator)),
    m_top(new StaticObject(*m_simulator,  Point(8,14), Point(13,1))),
    m_bot(new StaticObject(*m_simulator,  Point(8,0),Point(13,1))),
    m_left(new StaticObject(*m_simulator, Point(0,7),Point(1,13))),
    m_right(new StaticObject(*m_simulator,Point(16,7), Point(1,13))),
    m_block0(new StaticObject(*m_simulator, Point(9,8),   Point(0.35,0.35))),
    m_block1(new StaticObject(*m_simulator, Point(9,6),  Point(0.35,0.35))),
    m_block2(new StaticObject(*m_simulator, Point(7,8),  Point(0.35,0.35))),
    m_block3(new StaticObject(*m_simulator, Point(7,6), Point(0.35,0.35))),
    m_grid(new Grid(50,50))
{
    WallState *wallstate0 = new WallState(m_wallids, WallState::WallTypeSolid, Point(9,8));
    WallState *wallstate1 = new WallState(m_wallids, WallState::WallTypeSolid, Point(9,6));
    WallState *wallstate2 = new WallState(m_wallids, WallState::WallTypeSolid, Point(7,8));
    WallState *wallstate3 = new WallState(m_wallids, WallState::WallTypeSolid, Point(7,6));

    m_gameState.addWall(wallstate0);
    m_gameState.addWall(wallstate1);
    m_gameState.addWall(wallstate2);
    m_gameState.addWall(wallstate3);
}

GameEngineImpl::~GameEngineImpl()
{
    delete m_player;
    delete m_simulator;
    delete m_grid;
    delete m_top;
    delete m_bot;
    delete m_left;
    delete m_right;
    delete m_block0;
    delete m_block1;
    delete m_block2;
    delete m_block3;
    deleteAllWallObjects();
}

void GameEngineImpl::updateGameState(const InputState &inputState, double time)
{
    PlayerState playerState = m_gameState.getPlayerState();
    m_inputState = inputState;

    m_gameState.removeAllObjectsWithDestroyedFlag();

    deleteAllWallObjects();
    std::vector<const WallState*> allWalls = m_gameState.getAllChangedWalls();

    m_gameState.reduceAllBombsLifeTime(time);
    m_gameState.deleteAllBombsWithNegativeLifeTime(playerState);

    if (m_inputState.isUpKeyPressed() && playerState.getDirection() == PlayerState::PlayerDirectionUp)
    {
        m_player->applyLinearVelocity(0,playerState.getPlayerSpeed());
    }
    else if (m_inputState.isDownKeyPressed() && playerState.getDirection() == PlayerState::PlayerDirectionDown)
    {
        m_player->applyLinearVelocity(0,-1.0*playerState.getPlayerSpeed());
    }
    else if (m_inputState.isLeftKeyPressed() && playerState.getDirection() == PlayerState::PlayerDirectionLeft)
    {
        m_player->applyLinearVelocity(-1.0*playerState.getPlayerSpeed(),0);
    }
    else if (m_inputState.isRightKeyPressed() && playerState.getDirection() == PlayerState::PlayerDirectionRight)
    {
        m_player->applyLinearVelocity(playerState.getPlayerSpeed(),0);
    }
    else if (m_inputState.isUpKeyPressed())
    {
        playerState.setDirectionUp();
        m_player->applyLinearVelocity(0,5);
    }
    else if (m_inputState.isDownKeyPressed())
    {
        playerState.setDirectionDown();
        m_player->applyLinearVelocity(0,-5);
    }
    else if (m_inputState.isLeftKeyPressed())
    {
        playerState.setDirectionLeft();
        m_player->applyLinearVelocity(-5,0);
    }
    else if (m_inputState.isRightKeyPressed())
    {
        playerState.setDirectionRight();
        m_player->applyLinearVelocity(5,0);
    }
    else
    {
        m_player->applyLinearVelocity(0,0);
    }

    m_simulator->simulateStep(time);
    playerState.setPosition(m_player->getPosition());

    if (m_inputState.isSpaceKeyPressed())
    {
        if(playerState.getBombCount() == 0)
        {
            BombState *bombPlaced = new BombState(m_bombids);
            bombPlaced->setPosition(m_player->getPosition());
            m_grid->addBombAtPlace(*bombPlaced);
            playerState.countBomb();
            m_gameState.addBomb(bombPlaced);
            m_bombBox = new StaticObject(*m_simulator,m_player->getPosition() , Point(0.35,0.35));
        }
    }

    m_gameState.setPlayerState(playerState);
}

const Common::GameState &GameEngineImpl::getGameState() const
{
    return m_gameState;
}

void GameEngineImpl::deleteAllWallObjects()
{
    for(unsigned int i=0; i<m_wallObjects.size(); i++)
    {
        delete m_wallObjects[i];
    }
    m_wallObjects.clear();
}
