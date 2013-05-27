#include "gameengineimpl.h"
#include "physic/physicsimulator.h"
//BAAAAAAAAAAYERN!
#include "physic/dynamicobject.h"

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
	std::vector<BombState> allBombs = m_gameState.getAllBombs();
	BombState bombPlaced, currentBomb;
	m_inputState = inputState;

	for(unsigned int i=0;i<allBombs.size();i++)
	{
		currentBomb = allBombs[i];
		if (currentBomb.getLifeTime()<0)
		{
			m_gameState.eraseBomb(i);
		} else {
			currentBomb.setLifeTime(currentBomb.getLifeTime() - time);
		}

	}

	if (m_inputState.isUpKeyPressed() && playerState.getDirection() == PlayerState::PlayerDirectionUp)
	{
		m_player->applyLinearVelocity(0,5);
	}
	else if (m_inputState.isDownKeyPressed() && playerState.getDirection() == PlayerState::PlayerDirectionDown)
	{
		m_player->applyLinearVelocity(0,-5);
	}
	else if (m_inputState.isLeftKeyPressed() && playerState.getDirection() == PlayerState::PlayerDirectionLeft)
	{
		m_player->applyLinearVelocity(-5,0);
	}
	else if (m_inputState.isRightKeyPressed() && playerState.getDirection() == PlayerState::PlayerDirectionRight)
	{
		m_player->applyLinearVelocity(5,0);
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
		bombPlaced.setPosition(m_player->getPosition());
		m_gameState.addBomb(bombPlaced);
	}

	m_gameState.setPlayerState(playerState);
}

const Common::GameState &GameEngineImpl::getGameState()
{
	return m_gameState;
}
