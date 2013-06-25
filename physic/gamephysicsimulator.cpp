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

GamePhysicSimulator::GamePhysicSimulator(const LevelDefinition &level) :
	m_simulator(new PhysicSimulator),
	m_upperBorder(new StaticObject(*m_simulator, Point(0, level.getHeight()), level.getWidth(), 1)),
	m_lowerBorder(new StaticObject(*m_simulator, Point(0, -1), level.getWidth(), 1)),
	m_leftBorder(new StaticObject(*m_simulator, Point(-1, 0), 1, level.getHeight())),
	m_rightBorder(new StaticObject(*m_simulator, Point(level.getWidth(), 0), 1, level.getHeight()))
{ }

GamePhysicSimulator::~GamePhysicSimulator()
{
	deleteAllWalls();
	deleteAllBombs();
	deleteAllPlayers();
	delete m_upperBorder;
	delete m_lowerBorder;
	delete m_leftBorder;
	delete m_rightBorder;
	delete m_simulator;
}

void GamePhysicSimulator::simulateStep(GameState &game, double time)
{
	vector<unsigned int> playerIDs = game.getAllPossiblePlayerIDs();

	for (vector<unsigned int>::const_iterator i = playerIDs.begin(); i != playerIDs.end(); ++i)
	{
		const PlayerState& playerState = game.getPlayerStateById(*i);
		map<const PlayerState*, Player*>::iterator playerPosition = m_players.find(&playerState);
		Player *player = 0;

		if (playerPosition == m_players.end())
		{
			player = new Player(*m_simulator, playerState);
			m_players.insert(pair<const PlayerState*, Player*>(&playerState, player));
		}
		else
			player = playerPosition->second;

		player->applyLinearVelocity(playerState.getSpeedIntoX(), playerState.getSpeedIntoY());
		player->updateObstacle();
	}

	m_simulator->simulateStep(time);

	for (vector<unsigned int>::const_iterator i = playerIDs.begin(); i != playerIDs.end(); ++i)
	{
		PlayerState& playerState = game.getPlayerStateById(*i);
		Player *player = m_players.at(&playerState);
		playerState.setPosition(player->getPosition());
	}
}

void GamePhysicSimulator::updateItems(const GameState &state)
{
	updateBombs(state);
	updateWalls(state);
	updateCollisionGroups(state);
	updatePlayers(state);
}

void GamePhysicSimulator::deleteAllWalls()
{
	for(map<const WallState*, Wall*>::iterator i = m_walls.begin(); i != m_walls.end(); i++)
		delete i->second;

	m_walls.clear();
}

void GamePhysicSimulator::deleteAllBombs()
{
	for(map<const BombState*, Bomb*>::iterator i = m_bombs.begin(); i != m_bombs.end(); i++)
		delete i->second;

	m_bombs.clear();
}

void GamePhysicSimulator::deleteAllPlayers()
{
	for(map<const PlayerState*, Player*>::iterator i = m_players.begin(); i != m_players.end(); i++)
		delete i->second;

	m_players.clear();
}

void GamePhysicSimulator::updateBombs(const GameState &state)
{
	vector<const BombState*> changedBombs = state.getAllChangedBombs();

	for (vector<const BombState*>::const_iterator i = changedBombs.begin(); i != changedBombs.end(); ++i)
		updateBomb(*i);
}

void GamePhysicSimulator::updateBomb(const BombState *bomb)
{
	map<const BombState*, Bomb*>::iterator position = m_bombs.find(bomb);
	bool bombFound = position != m_bombs.end();
	Bomb *bombObject = 0;

	if (bombFound)
		bombObject = position->second;
	else
	{
		bombObject = new Bomb(*m_simulator, *bomb);
		m_bombs.insert(pair<const BombState*, Bomb*>(bomb, bombObject));
		position = m_bombs.find(bomb);
	}

	if (bomb->isDestroyed())
	{
		m_bombs.erase(position);
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
	map<const WallState*, Wall*>::iterator position = m_walls.find(wall);
	bool wallFound = position != m_walls.end();
	Wall *wallObject = 0;

	if (wallFound)
		wallObject = position->second;
	else
	{
		wallObject = new Wall(*m_simulator, *wall);
		m_walls.insert(pair<const WallState*, Wall*>(wall, wallObject));
		position = m_walls.find(wall);
	}

	if (wall->isDestroyed())
	{
		m_walls.erase(position);
		delete wallObject;
	}
}

void GamePhysicSimulator::updateCollisionGroups(const GameState &state)
{
	for (map<const BombState*, Bomb*>::iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
	{
		Bomb *bomb = i->second;
		bomb->collideWithEverything();
	}

	vector<const PlayerState*> allPlayers = state.getAllPlayers();
	for (vector<const PlayerState*>::const_iterator i = allPlayers.begin(); i != allPlayers.end(); ++i)
		updateCollisionGroupsForPlayer(**i);
}

void GamePhysicSimulator::updateCollisionGroupsForPlayer(const PlayerState &player)
{
	vector<const BombState*> bombsNotToCollideWith = player.getBombsNotToCollideWith();
	for (vector<const BombState*>::const_iterator i = bombsNotToCollideWith.begin(); i != bombsNotToCollideWith.end(); ++i)
	{
		const BombState &bombState = **i;
		if (!bombState.isDestroyed())
		{
			Bomb *bomb = m_bombs.at(&bombState);
			bomb->doNotCollideWith(player);
		}
	}
}

void GamePhysicSimulator::updatePlayers(const GameState &state)
{
	vector<const PlayerState*> allPlayers = state.getAllPlayers();

	for (vector<const PlayerState*>::const_iterator i = allPlayers.begin(); i != allPlayers.end(); ++i)
		updatePlayer(**i);
}

void GamePhysicSimulator::updatePlayer(const PlayerState &player)
{
	if (player.isDestroyed())
	{
		map<const PlayerState*, Player*>::iterator position = m_players.find(&player);
		delete position->second;
		m_players.erase(position);
	}
}
