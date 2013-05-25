#include "gameengineimpl.h"
#include "physicsimulator.h"
//BAAAAAAAAAAYERN!
#include "dynamicobject.h"

using namespace GameEngine;
using namespace Common;
using namespace Physic;

GameEngineImpl::GameEngineImpl() :
	m_simulator(new PhysicSimulator),
	m_player(new DynamicObject(*m_simulator))
{ }

GameEngineImpl::~GameEngineImpl()
{
	delete m_player;
	delete m_simulator;
}

void GameEngineImpl::updateGameState(const InputState &inputState, double time)
{
	PlayerState playerState = m_gameState.getPlayerState();
//    BombState bombPlaced;
	m_inputState = inputState;

	if (m_inputState.isUpKeyPressed())
	{
		playerState.setDirectionUp();
        m_player->applyLinearVelocity(0,5);
	}
	else if (m_inputState.isDownKeyPressed())
	{
		playerState.setDirectionDown();
        m_player->applyLinearVelocity(0,-5);
	} else if (m_inputState.isLeftKeyPressed())
	{
		playerState.setDirectionLeft();
        m_player->applyLinearVelocity(-5,0);
	} else if (m_inputState.isRightKeyPressed())
	{
		playerState.setDirectionRight();
        m_player->applyLinearVelocity(5,0);
	} else
	{
        m_player->applyLinearVelocity(0,0);
	}
	m_simulator->simulateStep(time);
	playerState.setPosition(m_player->getPosition());

/*    if (m_inputState.isSpaceKeyPressed())
    {
        bombPlaced.setPosition(m_player->getPosition());
        m_gameState.addBomb(bombPlaced);
    }
*/
	m_gameState.setPlayerState(playerState);
}

const Common::GameState &GameEngineImpl::getGameState()
{
	return m_gameState;
}
