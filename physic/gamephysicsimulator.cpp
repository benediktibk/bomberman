#include "physic/gamephysicsimulator.h"
#include "physic/physicsimulator.h"
#include "physic/dynamicobject.h"
#include "physic/staticobject.h"
#include "physic/player.h"
#include "physic/wall.h"
#include "physic/bomb.h"
#include "common/playerstate.h"
#include "common/gamestate.h"
#include "common/leveldefinition.h"

using namespace Physic;
using namespace Common;
using namespace std;

GamePhysicSimulator::GamePhysicSimulator(const LevelDefinition &level, const PlayerState &player) :
	m_simulator(new PhysicSimulator),
	m_player(new Player(*m_simulator, player.getPosition(), player.getWidth(), player.getHeight())),
	m_upperBorder(new StaticObject(*m_simulator, Point(0, level.getLevelHeight()), level.getLevelWidth(), 1)),
	m_lowerBorder(new StaticObject(*m_simulator, Point(0, -1), level.getLevelWidth(), 1)),
	m_leftBorder(new StaticObject(*m_simulator, Point(-1, 0), 1, level.getLevelHeight())),
	m_rightBorder(new StaticObject(*m_simulator, Point(level.getLevelWidth(), 0), 1, level.getLevelHeight()))
{ }

GamePhysicSimulator::~GamePhysicSimulator()
{
	deleteAllWallObjects();
	deleteAllBombObjects();
	delete m_upperBorder;
	delete m_lowerBorder;
	delete m_leftBorder;
	delete m_rightBorder;
	delete m_player;
	delete m_simulator;
}

void GamePhysicSimulator::simulateStep(PlayerState &player, double time)
{
	m_player->applyLinearVelocity(player.getSpeedIntoX(), player.getSpeedIntoY());
	m_simulator->simulateStep(time);
	player.setPosition(m_player->getPosition());
}

void GamePhysicSimulator::updateItems(const GameState &state)
{
	updateBombs(state);
	updateWalls(state);
}

void GamePhysicSimulator::deleteAllWallObjects()
{
	for(map<const WallState*, Wall*>::iterator i = m_wallObjects.begin(); i != m_wallObjects.end(); i++)
		delete i->second;

	m_wallObjects.clear();
}

void GamePhysicSimulator::deleteAllBombObjects()
{
	for(map<const BombState*, Bomb*>::iterator i = m_bombObjects.begin(); i != m_bombObjects.end(); i++)
		delete i->second;

	m_bombObjects.clear();
}

void GamePhysicSimulator::updateBombs(const GameState &state)
{
	vector<const BombState*> changedBombs = state.getAllChangedBombs();

	for (vector<const BombState*>::const_iterator i = changedBombs.begin(); i != changedBombs.end(); ++i)
		updateBomb(*i);
}

void GamePhysicSimulator::updateBomb(const BombState *bomb)
{
	map<const BombState*, Bomb*>::iterator position = m_bombObjects.find(bomb);
	bool bombFound = position != m_bombObjects.end();
	Bomb *bombObject = 0;

	if (bombFound)
		bombObject = position->second;
	else
	{
		bombObject = new Bomb(*m_simulator, *bomb);
		m_bombObjects.insert(pair<const BombState*, Bomb*>(bomb, bombObject));
		position = m_bombObjects.find(bomb);
	}

	if (bomb->isDestroyed())
	{
		m_bombObjects.erase(position);
		delete bombObject;
	}
}

void GamePhysicSimulator::updateWalls(const GameState &state)
{
	vector<const WallState*> changedWalls = state.getAllChangedWalls();

	for (vector<const WallState*>::const_iterator i = changedWalls.begin(); i != changedWalls.end(); ++i)
		updateWall(*i);
}

void GamePhysicSimulator::updateWall(const WallState *wall)
{
	map<const WallState*, Wall*>::iterator position = m_wallObjects.find(wall);
	bool wallFound = position != m_wallObjects.end();
	Wall *wallObject = 0;

	if (wallFound)
		wallObject = position->second;
	else
	{
		wallObject = new Wall(*m_simulator, *wall);
		m_wallObjects.insert(pair<const WallState*, Wall*>(wall, wallObject));
		position = m_wallObjects.find(wall);
	}

	if (wall->isDestroyed())
	{
		m_wallObjects.erase(position);
		delete wallObject;
	}
}
