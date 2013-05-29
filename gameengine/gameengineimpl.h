#ifndef GAMEENGINE_GAMEENGINEIMPL_H
#define GAMEENGINE_GAMEENGINEIMPL_H

#include "common/gameengine.h"
#include "common/uniqueidcreator.h"
#include "common/leveldefinition.h"
#include <map>

namespace Physic
{
class PhysicSimulator;
class DynamicObject;
class StaticObject;
}

namespace GameEngine
{
class Grid;

class GameEngineImpl :
		public Common::GameEngine
{
public:
	GameEngineImpl();
	virtual ~GameEngineImpl();

	virtual void updateGameState(const Common::InputState &inputState, double time);
	virtual const Common::GameState& getGameState() const;

private:
	void deleteAllWallObjects();
	void updatePlayerSpeed();
	void updateBombs();
	void placeBombs();
	void updateWalls();
	void updateWall(const Common::WallState *wall);

private:
	Common::InputState m_inputState;
	Common::UniqueIdCreator m_bombids;
	Common::UniqueIdCreator m_wallids;
	Common::GameState m_gameState;
	Common::PlayerState m_playerState;
	double m_elapsedTime;
	Physic::PhysicSimulator *m_simulator;
	Physic::DynamicObject *m_player;
	Physic::StaticObject *m_upperBorder;
	Physic::StaticObject *m_lowerBorder;
	Physic::StaticObject *m_leftBorder;
	Physic::StaticObject *m_rightBorder;
	std::map<const Common::WallState*, Physic::StaticObject*> m_wallObjects;
	Grid *m_grid;
	bool m_firstGameStateUpdate;
};
}

#endif
