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
	m_inputState = inputState;

	if(m_inputState.isUpKeyPressed())
	{
		double additionalPosition = 5;
		PlayerState playerState = m_gameState.getPlayerState();
		double oldPosition = playerState.getPosition();
		playerState.setPosition(oldPosition + additionalPosition);
		m_gameState.setPlayerState(playerState);
	}

	if(m_inputState.isDownKeyPressed())
	{
		double additionalPosition = 5;
		PlayerState playerState = m_gameState.getPlayerState();
		double oldPosition = playerState.getPosition();
		playerState.setPosition(oldPosition - additionalPosition);
		m_gameState.setPlayerState(playerState);
	}

	m_simulator->simulateStep(time);
}

const Common::GameState &GameEngineImpl::getGameState()
{
	return m_gameState;
}
