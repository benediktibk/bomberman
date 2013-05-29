#ifndef GAMEENGINE_GAMEENGINEIMPL_H
#define GAMEENGINE_GAMEENGINEIMPL_H

#include "common/gameengine.h"
#include "common/uniqueidcreator.h"
namespace Physic
{
class PhysicSimulator;
class DynamicObject;
class StaticObject;
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
    void deleteAllWallObjects();

private:
    Common::InputState m_inputState;
    Common::UniqueIdCreator m_bombids;
    Common::UniqueIdCreator m_wallids;
    Common::GameState m_gameState;
    Physic::PhysicSimulator *m_simulator;
    Physic::DynamicObject *m_player;
    Physic::StaticObject *m_top;
    Physic::StaticObject *m_bot;
    Physic::StaticObject *m_left;
    Physic::StaticObject *m_right;
    Physic::StaticObject *m_block0;
    Physic::StaticObject *m_block1;
    Physic::StaticObject *m_block2;
    Physic::StaticObject *m_block3;
    std::vector<Physic::StaticObject*> m_wallObjects;
    Physic::StaticObject *m_bombBox;
};
}

#endif
