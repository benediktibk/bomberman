#ifndef GAMEENGINE_GAMEENGINEIMPL_H
#define GAMEENGINE_GAMEENGINEIMPL_H

#include "common/gameengine.h"
#include "common/uniqueidcreator.h"
namespace Physic
{
class PhysicSimulator;
class DynamicObject;
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
	Common::GameState m_gameState;
	Physic::PhysicSimulator *m_simulator;
    Physic::DynamicObject *m_player;
};
}

#endif
