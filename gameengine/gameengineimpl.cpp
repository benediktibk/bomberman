#include "gameengine/gameengineimpl.h"
#include "gameengine/grid.h"
#include "physic/gamephysicsimulator.h"
//BAAAAAAAAAAYERN!
#include "physic/player.h"
#include "physic/staticobject.h"
#include "physic/collisiongroups.h"
#include <assert.h>
#include <algorithm>

using namespace GameEngine;
using namespace Common;
using namespace Physic;
using namespace std;

GameEngineImpl::GameEngineImpl(const LevelDefinition &level, unsigned int playerCount) :
	m_gameState(level, playerCount, m_playerIds, m_wallids),
	m_playerState(m_gameState.getFirstPlayerState()),
	m_grid(new Grid(level.getLevelHeight(), level.getLevelWidth())),
	m_firstGameStateUpdate(true),
	m_simulator(new GamePhysicSimulator(level))
{
	vector<const WallState*> walls = m_gameState.getAllChangedWalls();

	for (vector<const WallState*>::const_iterator i = walls.begin(); i != walls.end(); ++i)
		m_grid->addWallAtPlace(**i);
}

GameEngineImpl::~GameEngineImpl()
{
	delete m_grid;
	delete m_simulator;
}

void GameEngineImpl::updateGameState(const InputState &inputState, double time)
{
	m_inputState = inputState;
	m_elapsedTime = time;

	if (!m_firstGameStateUpdate)
		m_gameState.resetChangedFlags();
	m_gameState.removeAllObjectsWithDestroyedFlag();
	updateBombs();
	updatePlayerPosition();
	placeBombs();
	m_simulator->updateItems(m_gameState);
//    applyPowerUps();

	m_firstGameStateUpdate = false;
}

const Common::GameState &GameEngineImpl::getGameState() const
{
	return m_gameState;
}

Common::GameState &GameEngineImpl::getGameState()
{
	return m_gameState;
}

void GameEngineImpl::updatePlayerVelocity()
{
	if (m_inputState.isMoreThanOneMovementButtonPressed())
		setPlayerSpeedIfMoreThanOneDirectionIsSelected();
	else if (m_inputState.isMovementButtonPressed())
		setPlayerSpeedIntoOnlySelectedDirection();
	else
		setPlayerSpeedToNull();
}

void GameEngineImpl::updatePlayerPosition()
{
	double realSimulatedTime = 0;
	vector<GridPoint> playerFields = m_grid->getPlayerFields(m_playerState);

	if (playerFields.size() == 1)
		updatePlayerVelocity();

	double timeTillPlayerReachesGridPoint = getTimeTillPlayerReachesGridPoint();

	if (timeTillPlayerReachesGridPoint < m_elapsedTime)
	{
		m_simulator->simulateStep(m_gameState, timeTillPlayerReachesGridPoint);
		GridPoint gridPosition(m_playerState.getPosition());
		m_playerState.setPosition(gridPosition.getPointPosition());
		realSimulatedTime += timeTillPlayerReachesGridPoint;
		updatePlayerVelocity();
	}

	m_simulator->simulateStep(m_gameState, m_elapsedTime - realSimulatedTime);

	playerFields = m_grid->getPlayerFields(m_playerState);
	vector<const BombState*> bombsNotToCollideWith = m_playerState.getBombsNotToCollideWith();
	for (vector<const BombState*>::const_iterator i = bombsNotToCollideWith.begin(); i != bombsNotToCollideWith.end(); ++i)
	{
		GridPoint gridPosition((*i)->getPosition());

		if (count(playerFields.begin(), playerFields.end(), gridPosition) == 0)
			m_playerState.removeBombFromDoNotCollideList(*i);
	}
}

void GameEngineImpl::setPlayerSpeedIfMoreThanOneDirectionIsSelected()
{
	assert(m_inputState.isMoreThanOneMovementButtonPressed());
	assert(m_inputState.isMovementButtonPressed());

	if (m_inputState.isUpKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionUp)
		m_playerState.setMoving();
	else if (m_inputState.isDownKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionDown)
		m_playerState.setMoving();
	else if (m_inputState.isLeftKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionLeft)
		m_playerState.setMoving();
	else if (m_inputState.isRightKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionRight)
		m_playerState.setMoving();
}

void GameEngineImpl::setPlayerSpeedIntoOnlySelectedDirection()
{
	assert(!m_inputState.isMoreThanOneMovementButtonPressed());
	assert(m_inputState.isMovementButtonPressed());

	if (m_inputState.isUpKeyPressed())
	{
		m_playerState.setDirectionUp();
		m_playerState.setMoving();
	}
	else if (m_inputState.isDownKeyPressed())
	{
		m_playerState.setDirectionDown();
		m_playerState.setMoving();
	}
	else if (m_inputState.isLeftKeyPressed())
	{
		m_playerState.setDirectionLeft();
		m_playerState.setMoving();
	}
	else if (m_inputState.isRightKeyPressed())
	{
		m_playerState.setDirectionRight();
		m_playerState.setMoving();
	}
}

void GameEngineImpl::setPlayerSpeedToNull()
{
	m_playerState.setNotMoving();
}

double GameEngineImpl::getTimeTillPlayerReachesGridPoint() const
{
	double velocityX = m_playerState.getSpeedIntoX();
	double velocityY = m_playerState.getSpeedIntoY();
	const Point &position = m_playerState.getPosition();
	const GridPoint gridPosition(position);
	double time = 0;

	if (velocityX != 0)
	{
		if (velocityX > 0)
			time = (position.getX() - gridPosition.getX())/velocityX;
		else
			time = (position.getX() - (gridPosition.getX() + 1))/velocityX;
	}

	if (velocityY != 0)
	{
		if (velocityY > 0)
			time = (position.getY() - gridPosition.getY())/velocityY;
		else
			time = (position.getY() - (gridPosition.getY() + 1))/velocityY;
	}

	return max(0.0, time);
}

void GameEngineImpl::updateBombs()
{
	vector<const BombState*> bombsWithNoLifeTime;

	m_gameState.reduceAllBombsLifeTime(m_elapsedTime);
	bombsWithNoLifeTime = m_gameState.getAllBombsWithNoLifeTime();

	for (size_t i = 0; i < bombsWithNoLifeTime.size(); i++)
	{
		const BombState &bomb = *bombsWithNoLifeTime[i];

		vector<unsigned int> wallsInRange;
		wallsInRange = m_grid->getWallsInRange(bomb);
		for(size_t j = 0; j < wallsInRange.size(); j++)
			m_gameState.eraseWallById(wallsInRange[j]);

		vector<unsigned int> bombsInRange;
		bombsInRange = m_grid->getBombsInRange(bomb);
		for(size_t j = 0; j < bombsInRange.size(); j++)
			m_gameState.setBombsLifeTimeToZero(bombsInRange[j]);

		vector<unsigned int> powerUpsInRange;
		powerUpsInRange = m_grid->getPowerUpsInRange(bomb);
		for(size_t j = 0; j < powerUpsInRange.size(); j++)
			m_gameState.erasePowerUpById(powerUpsInRange[j]);
	}

	m_gameState.setAllBombsWithNoLifeTimeDestroyed(m_playerState);

	bombsWithNoLifeTime = m_gameState.getAllBombsWithNoLifeTime();
	for (vector<const BombState*>::const_iterator i = bombsWithNoLifeTime.begin(); i != bombsWithNoLifeTime.end(); ++i)
		m_playerState.removeBombFromDoNotCollideList(*i);
}

void GameEngineImpl::placeBombs()
{
	if (m_inputState.isSpaceKeyPressed() && m_playerState.canPlayerPlaceBomb())
	{
		BombState *bombPlaced = new BombState(m_bombids);
		bombPlaced->setPosition(m_playerState.getCenterPosition());
		m_grid->addBombAtPlace(*bombPlaced);
		m_playerState.countBomb();
		m_playerState.doNotCollideWith(bombPlaced);
		m_gameState.addBomb(bombPlaced);
	}
}

/*
void GameEngineImpl::applyPowerUps()
{
	std::vector<GridPoint> playerField = m_grid->getPlayerFields(m_player);
  for (vector<const WallState*>::const_iterator i = changedWalls.begin(); i != changedWalls.end(); ++i)
	std::vector<unsigned int> powerUpField = m_grid->
}

*/
