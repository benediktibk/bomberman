#include "gameengineimpl.h"
#include "physic/physicsimulator.h"
//BAAAAAAAAAAYERN!
#include "physic/dynamicobject.h"
#include "physic/staticobject.h"
#include "grid.h"
#include <assert.h>

using namespace GameEngine;
using namespace Common;
using namespace Physic;
using namespace std;

GameEngineImpl::GameEngineImpl(const LevelDefinition &level) :
	m_gameState(level,m_playerIds),
	m_playerState(m_gameState.getPlayerState()),
	m_simulator(new PhysicSimulator),
	m_player(new DynamicObject(*m_simulator, m_playerState.getPosition(), m_playerState.getWidth(), m_playerState.getHeight())),
	m_upperBorder(new StaticObject(*m_simulator, Point(0, level.getLevelHeight()), level.getLevelWidth(), 1)),
	m_lowerBorder(new StaticObject(*m_simulator, Point(0, -1), level.getLevelWidth(), 1)),
	m_leftBorder(new StaticObject(*m_simulator, Point(-1, 0), 1, level.getLevelHeight())),
	m_rightBorder(new StaticObject(*m_simulator,Point(level.getLevelWidth(), 0), 1, level.getLevelHeight())),
	m_grid(new Grid(level.getLevelHeight(), level.getLevelWidth())),
	m_firstGameStateUpdate(true)
{
	for(unsigned int x=0;x<level.getLevelWidth();x++)
	{
		for(unsigned int y=0;y<level.getLevelHeight();y++)
		{
			if(level.getObjectTypeAtPosition(x,y) == LevelDefinition::ObjectTypeSolidWall)
			{
				WallState *wallstate = new WallState(m_wallids, WallState::WallTypeSolid, Point(x, y));
				m_gameState.addWall(wallstate);
				m_grid->addWallAtPlace(*wallstate);
			}
			if(level.getObjectTypeAtPosition(x,y) == LevelDefinition::ObjectTypeLooseWall)
			{
				WallState *wallstate = new WallState(m_wallids, WallState::WallTypeLoose, Point(x, y));
				m_gameState.addWall(wallstate);
				m_grid->addWallAtPlace(*wallstate);
			}
			if(level.getObjectTypeAtPosition(x,y) == LevelDefinition::ObjectTypePlayer)
			{
				//m_playerState.setPosition(Point(x,y)); Dynamik Position auf diese ändern
			}
		}
	}
}

GameEngineImpl::~GameEngineImpl()
{
	deleteAllWallObjects();
	deleteAllBombObjects();
	delete m_player;
	delete m_grid;
	delete m_upperBorder;
	delete m_lowerBorder;
	delete m_leftBorder;
	delete m_rightBorder;
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
	updateWalls();
	updatePlayerPosition();
	placeBombs();

	m_firstGameStateUpdate = false;
}

const Common::GameState &GameEngineImpl::getGameState() const
{
	return m_gameState;
}

void GameEngineImpl::deleteAllWallObjects()
{
	for(map<const WallState*, StaticObject*>::iterator i = m_wallObjects.begin(); i != m_wallObjects.end(); i++)
		delete i->second;

	m_wallObjects.clear();
}

void GameEngineImpl::deleteAllBombObjects()
{
	for(map<const BombState*, StaticObject*>::iterator i = m_bombObjects.begin(); i != m_bombObjects.end(); i++)
		delete i->second;

	m_bombObjects.clear();
}

void GameEngineImpl::updatePlayerPosition()
{
	if (m_inputState.isMoreThanOneMovementButtonPressed())
		setPlayerSpeedIfMoreThanOneDirectionIsSelected();
	else if (m_inputState.isMovementButtonPressed())
		setPlayerSpeedIntoOnlySelectedDirection();
	else
		setPlayerSpeedToNull();

	m_simulator->simulateStep(m_elapsedTime);
	m_playerState.setPosition(m_player->getPosition());
}

void GameEngineImpl::setPlayerSpeedIfMoreThanOneDirectionIsSelected()
{
	assert(m_inputState.isMoreThanOneMovementButtonPressed());
	assert(m_inputState.isMovementButtonPressed());

	if (m_inputState.isUpKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionUp)
		m_player->applyLinearVelocity(0, m_playerState.getSpeed());
	else if (m_inputState.isDownKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionDown)
		m_player->applyLinearVelocity(0, (-1)*m_playerState.getSpeed());
	else if (m_inputState.isLeftKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionLeft)
		m_player->applyLinearVelocity((-1)*m_playerState.getSpeed(), 0);
	else if (m_inputState.isRightKeyPressed() && m_playerState.getDirection() == PlayerState::PlayerDirectionRight)
		m_player->applyLinearVelocity(m_playerState.getSpeed(), 0);
}

void GameEngineImpl::setPlayerSpeedIntoOnlySelectedDirection()
{
	assert(!m_inputState.isMoreThanOneMovementButtonPressed());
	assert(m_inputState.isMovementButtonPressed());

	if (m_inputState.isUpKeyPressed())
	{
		m_playerState.setDirectionUp();
		m_player->applyLinearVelocity(0, m_playerState.getSpeed());
	}
	else if (m_inputState.isDownKeyPressed())
	{
		m_playerState.setDirectionDown();
		m_player->applyLinearVelocity(0, (-1)*m_playerState.getSpeed());
	}
	else if (m_inputState.isLeftKeyPressed())
	{
		m_playerState.setDirectionLeft();
		m_player->applyLinearVelocity((-1)*m_playerState.getSpeed(), 0);
	}
	else if (m_inputState.isRightKeyPressed())
	{
		m_playerState.setDirectionRight();
		m_player->applyLinearVelocity(m_playerState.getSpeed(), 0);
	}
}

void GameEngineImpl::setPlayerSpeedToNull()
{
	m_player->applyLinearVelocity(0, 0);
}

void GameEngineImpl::updateBombs()
{
	vector<const BombState*> BombsWithNegativeLiveTime;

	m_gameState.reduceAllBombsLifeTime(m_elapsedTime);
	BombsWithNegativeLiveTime = m_gameState.getAllBombsWithNegativeLifeTime();

	for(size_t i = 0; i < BombsWithNegativeLiveTime.size(); i++)
	{
		vector<unsigned int> wallsInRange;
		wallsInRange = m_grid->getWallsInRange(*BombsWithNegativeLiveTime[i]);
		for(size_t j = 0; j < wallsInRange.size(); j++)
		{
			m_gameState.eraseWallById(wallsInRange[j]);
		}
		/*vector<unsigned int> bombsInRange;
		bombsInRange = m_grid->getBombsInRange(*BombsWithNegativeLiveTime[i]);
		for(size_t j = 0; j < bombsInRange.size(); j++)
		{

		}*/

	}
	m_gameState.setAllBombsWithNegativeLifeTimeDestroyed(m_playerState);

	vector<const BombState*> changedBombs = m_gameState.getAllChangedBombs();

	for (vector<const BombState*>::const_iterator i = changedBombs.begin(); i != changedBombs.end(); ++i)
		updateBomb(*i);
}

void GameEngineImpl::updateBomb(const BombState *bomb)
{
	map<const BombState*, StaticObject*>::iterator position = m_bombObjects.find(bomb);
	bool bombFound = position != m_bombObjects.end();
	StaticObject *bombObject = 0;

	if (bombFound)
		bombObject = position->second;
	else
	{
		bombObject = new StaticObject(*m_simulator, bomb->getPosition(), 1, 1);
		m_bombObjects.insert(pair<const BombState*, StaticObject*>(bomb, bombObject));
		position = m_bombObjects.find(bomb);
	}

	if (bomb->isDestroyed())
	{
		m_bombObjects.erase(position);
		delete bombObject;
	}
}

void GameEngineImpl::placeBombs()
{
	if (m_inputState.isSpaceKeyPressed() && m_playerState.getBombCount() < 1)
	{
		BombState *bombPlaced = new BombState(m_bombids);
		bombPlaced->setPosition(m_player->getCenterPosition());
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
		wallObject = position->second;
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
