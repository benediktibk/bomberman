#include "gameengineimpl.h"
#include "physicsimulator.h"
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
	m_inputState = inputState;

	if (m_inputState.isUpKeyPressed())
    {
        playerState.setDirectionUp();
		m_player->applyForce(1000);
    }
    else if(m_inputState.isDownKeyPressed())
    {
        playerState.setDirectionDown();
        m_player->applyForce(-1000);
    } else
    {
        m_player->applyForce(0);
    }
    m_simulator->simulateStep(time);
	playerState.setPosition(m_player->getPosition());
	m_gameState.setPlayerState(playerState);
}

const Common::GameState &GameEngineImpl::getGameState()
{
	return m_gameState;
}
