#ifndef GAMEENGINE_GAMEENGINEIMPL_H
#define GAMEENGINE_GAMEENGINEIMPL_H

#include "common/gameengine.h"
#include "common/uniqueidcreator.h"
#include "common/leveldefinition.h"
#include "common/gridpoint.h"

namespace Physic
{
    class GamePhysicSimulator;
}

namespace GameEngine
{
    class Grid;

    class GameEngineImpl :
            public Common::GameEngine
    {
    public:
        GameEngineImpl(const Common::LevelDefinition &level, unsigned int playerCount);
        virtual ~GameEngineImpl();

        virtual void updateGameState(const std::map<unsigned int, Common::InputState> &inputStates, double time);
        virtual const Common::GameState& getGameState() const;
        virtual std::vector<unsigned int> getAllPossiblePlayerIDs() const;
        Common::GameState& getGameState();
        double getTimeTillOnePlayerReachesGridPoint() const;
        double getTimeTillPlayerReachesGridPoint(const Common::PlayerState &player) const;
        std::vector<Common::GridPoint> getAllPowerUpFields() const;

    private:
        void updatePlayerPositions();
        void updatePlayerVelocities();
        void updatePlayerVelocity(Common::PlayerState &player, const Common::InputState &input);
        void updatePlayerWithBombCollisions();
        void setPlayerSpeedIfMoreThanOneDirectionIsSelected(Common::PlayerState &player, const Common::InputState &input);
        void setPlayerSpeedIntoOnlySelectedDirection(Common::PlayerState &player, const Common::InputState &input);
        void setPlayerSpeedToNull(Common::PlayerState &player);
        void updateBombs();
        void placeBombs();
        void placeBombForPlayer(Common::PlayerState &player, const Common::InputState &input);

    private:
        std::map<unsigned int, Common::InputState> m_inputStates;
        Common::UniqueIdCreator m_bombids;
        Common::UniqueIdCreator m_wallids;
        Common::UniqueIdCreator m_playerIds;
        Common::GameState m_gameState;
        double m_elapsedTime;
        Grid *m_grid;
        bool m_firstGameStateUpdate;
        Physic::GamePhysicSimulator *m_simulator;
    };
}

#endif
