#include "gameengineimpl.h"
#include "physic/physicsimulator.h"
//BAAAAAAAAAAYERN!
#include "physic/dynamicobject.h"
#include "physic/staticobject.h"
#include "physic/topwall.h"
#include "physic/botwall.h"
#include "physic/wallleft.h"
#include "physic/wallright.h"

using namespace GameEngine;
using namespace Common;
using namespace Physic;

GameEngineImpl::GameEngineImpl() :
	m_simulator(new PhysicSimulator),
    m_player(new DynamicObject(*m_simulator)),
    m_block(new StaticObject(*m_simulator)),
    m_top(new TopWall(*m_simulator)),
    m_bot(new BotWall(*m_simulator)),
    m_left(new WallLeft(*m_simulator)),
    m_right(new WallRight(*m_simulator))
{

   // WallState wallstate;
  //  WallState wallstate1;
  //  WallState wallstate2;


    //wallstate.setPosition(Point(1,2));
   // wallstate1.setPosition(Point(-2,-1));
    //wallstate2.setPosition(Point(-2,0));

    //m_gameState.addWall(wallstate);
    //m_gameState.addWall(wallstate1);
    //m_gameState.addWall(wallstate2);

}


GameEngineImpl::~GameEngineImpl()
{
	delete m_player;
	delete m_simulator;
    delete m_block;
    delete m_top;
    delete m_bot;
}

void GameEngineImpl::updateGameState(const InputState &inputState, double time)
{
	PlayerState playerState = m_gameState.getPlayerState();
	std::vector<BombState*> allBombs = m_gameState.getAllBombs();
	m_inputState = inputState;


	for(unsigned int i=0;i<allBombs.size();i++)
	{
		BombState *currentBomb = allBombs[i];
		if (currentBomb->getLifeTime()<0)
		{
			m_gameState.eraseBomb(i);
            playerState.reduceBombCount();
		} else {
			currentBomb->setLifeTime(currentBomb->getLifeTime() - time);
		}

	}

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
        BombState *bombPlaced=new BombState(m_bombids);

        bombPlaced->setPosition(m_player->getPosition());
        playerState.countBomb();

		m_gameState.addBomb(bombPlaced);
        }
	}

	m_gameState.setPlayerState(playerState);

}

const Common::GameState &GameEngineImpl::getGameState() const
{
	return m_gameState;
}
