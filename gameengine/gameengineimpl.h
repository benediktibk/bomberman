#ifndef GAMEENGINE_GAMEENGINEIMPL_H
#define GAMEENGINE_GAMEENGINEIMPL_H

#include "common/gameengine.h"
#include "common/uniqueidcreator.h"
namespace Physic
{
class PhysicSimulator;
class DynamicObject;
class StaticObject;
class TopWall;
class BotWall;
class WallLeft;
class WallRight;
}

namespace GameEngine
{
class GameEngineImpl :
		public Common::GameEngine
{
public:
	GameEngineImpl();
	virtual ~GameEngineImpl();

	virtual void updateGameState(const Common::InputState &inputState, double time);
    virtual const Common::GameState& getGameState() const;

private:
	Common::InputState m_inputState;
    Common::UniqueIdCreator m_bombids;
    Common::UniqueIdCreator m_wallids;
	Common::GameState m_gameState;
	Physic::PhysicSimulator *m_simulator;
    Physic::DynamicObject *m_player;
    Physic::StaticObject *m_block;
    Physic::TopWall *m_top;
    Physic::BotWall *m_bot;
    Physic::WallLeft *m_left;
    Physic::WallRight *m_right;
};
}

#endif
