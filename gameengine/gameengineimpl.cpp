#include "gameengineimpl.h"
#include "physic/physicsimulator.h"
//BAAAAAAAAAAYERN!
#include "physic/dynamicobject.h"
#include "physic/staticobject.h"
#include "physic/topwall.h"
#include "physic/botwall.h"
#include "physic/wallleft.h"
#include "physic/wallright.h"
#include "grid.h"
#include "common/leveldefinition.h"

using namespace GameEngine;
using namespace Common;
using namespace Physic;

GameEngineImpl::GameEngineImpl() :
	m_simulator(new PhysicSimulator),
    m_player(new DynamicObject(*m_simulator)),
    m_grid(new Grid(50,50))
{ }

GameEngineImpl::~GameEngineImpl()
{
	delete m_player;
	delete m_simulator;
    delete m_grid;
}

void GameEngineImpl::updateGameState(const InputState &inputState, double time)
{
	PlayerState playerState = m_gameState.getPlayerState();
	m_inputState = inputState;

	m_gameState.removeAllObjectsWithDestroyedFlag();

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
		BombState *bombPlaced=new BombState(m_bombids);
        Point gridPoint;

        bombPlaced->setPosition(m_player->getPosition());
        gridPoint = m_grid->addBombAtPlace(*bombPlaced);
        bombPlaced->setPosition(gridPoint);
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
