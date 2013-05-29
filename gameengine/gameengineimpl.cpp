#include "gameengineimpl.h"
#include "physic/physicsimulator.h"
//BAAAAAAAAAAYERN!
#include "physic/dynamicobject.h"
#include "physic/staticobject.h"
#include "grid.h"

using namespace GameEngine;
using namespace Common;
using namespace Physic;
using namespace std;

GameEngineImpl::GameEngineImpl() :
	m_simulator(new PhysicSimulator),
	m_player(new DynamicObject(*m_simulator)),
	m_upperBorder(new StaticObject(*m_simulator, Point(8, 14), 13, 1)),
	m_lowerBorder(new StaticObject(*m_simulator, Point(8, 0), 13, 1)),
	m_leftBorder(new StaticObject(*m_simulator, Point(0, 7), 1, 13)),
	m_rightBorder(new StaticObject(*m_simulator,Point(16, 7), 1, 13)),
	m_grid(new Grid(50, 50)),
	m_firstGameStateUpdate(true)
{
	WallState *wallstate0 = new WallState(m_wallids, WallState::WallTypeSolid, Point(9, 8));
	WallState *wallstate1 = new WallState(m_wallids, WallState::WallTypeSolid, Point(9, 6));
	WallState *wallstate2 = new WallState(m_wallids, WallState::WallTypeSolid, Point(7, 8));
	WallState *wallstate3 = new WallState(m_wallids, WallState::WallTypeSolid, Point(7, 6));

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
	delete m_upperBorder;
	delete m_lowerBorder;
	delete m_leftBorder;
	delete m_rightBorder;
	deleteAllWallObjects();
}

void GameEngineImpl::updateGameState(const InputState &inputState, double time)
{
	m_inputState = inputState;
	m_playerState = m_gameState.getPlayerState();
	m_elapsedTime = time;

	if (!m_firstGameStateUpdate)
		m_gameState.resetChangedFlags();
	m_gameState.removeAllObjectsWithDestroyedFlag();
	updateBombs();
	updateWalls();
	updatePlayerSpeed();
	m_simulator->simulateStep(time);
	m_playerState.setPosition(m_player->getPosition());
	placeBombs();

	m_gameState.setPlayerState(m_playerState);
	m_firstGameStateUpdate = false;
}

const Common::GameState &GameEngineImpl::getGameState() const
{
	return m_gameState;
}

void GameEngineImpl::deleteAllWallObjects()
{
	for(map<const Common::WallState*, Physic::StaticObject*>::iterator i = m_wallObjects.begin(); i != m_wallObjects.end(); i++)
		delete i->second;

	m_wallObjects.clear();
}

void GameEngineImpl::updatePlayerSpeed()
{
	if (m_inputState.isUpKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionUp)
		m_player->applyLinearVelocity(0, m_playerState.getPlayerSpeed());
	else if (m_inputState.isDownKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionDown)
		m_player->applyLinearVelocity(0, (-1)*m_playerState.getPlayerSpeed());
	else if (m_inputState.isLeftKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionLeft)
		m_player->applyLinearVelocity((-1)*m_playerState.getPlayerSpeed(), 0);
	else if (m_inputState.isRightKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionRight)
		m_player->applyLinearVelocity(m_playerState.getPlayerSpeed(), 0);
	else if (m_inputState.isUpKeyPressed())
	{
		m_playerState.setDirectionUp();
		m_player->applyLinearVelocity(0, 5);
	}
	else if (m_inputState.isDownKeyPressed())
	{
		m_playerState.setDirectionDown();
		m_player->applyLinearVelocity(0, -5);
	}
	else if (m_inputState.isLeftKeyPressed())
	{
		m_playerState.setDirectionLeft();
		m_player->applyLinearVelocity(-5, 0);
	}
	else if (m_inputState.isRightKeyPressed())
	{
		m_playerState.setDirectionRight();
		m_player->applyLinearVelocity(5, 0);
	}
	else
		m_player->applyLinearVelocity(0, 0);
}

void GameEngineImpl::updateBombs()
{
	m_gameState.reduceAllBombsLifeTime(m_elapsedTime);
	m_gameState.deleteAllBombsWithNegativeLifeTime(m_playerState);
}

void GameEngineImpl::placeBombs()
{
	if (m_inputState.isSpaceKeyPressed() && m_playerState.getBombCount() < 1)
	{
		BombState *bombPlaced = new BombState(m_bombids);
		bombPlaced->setPosition(m_player->getPosition());
		m_grid->addBombAtPlace(*bombPlaced);
		m_playerState.countBomb();
		m_gameState.addBomb(bombPlaced);
	}
}

void GameEngineImpl::updateWalls()
{
	vector<const WallState*> changedWalls = m_gameState.getAllChangedWalls();

	for (vector<const WallState*>::const_iterator i = changedWalls.begin(); i != changedWalls.end(); ++i)
		updateWall(*i);
}

void GameEngineImpl::updateWall(const WallState *wall)
{
	map<const WallState*, StaticObject*>::iterator position = m_wallObjects.find(wall);
	bool wallFound = position != m_wallObjects.end();
	StaticObject *wallObject = 0;

	if (wallFound)
	{
		wallObject = position->second;
		wallObject->SetPosition(wall->getPosition());
	}
	else
	{
		wallObject = new StaticObject(*m_simulator, wall->getPosition(), 1, 1);
		m_wallObjects.insert(pair<const WallState*, StaticObject*>(wall, wallObject));
		position = m_wallObjects.find(wall);
	}

	if (wall->isDestroyed())
	{
		m_wallObjects.erase(position);
		delete wallObject;
	}
}
