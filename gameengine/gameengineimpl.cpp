#include "gameengine/gameengineimpl.h"
#include "gameengine/grid.h"
#include "physic/gamephysicsimulator.h"
//BAAAAAAAAAAYERN!
#include "physic/player.h"
#include "physic/staticobject.h"
#include "physic/collisiongroups.h"
#include "common/powerupgenerator.h"
#include <assert.h>
#include <algorithm>
#include <limits>
#include <math.h>

using namespace GameEngine;
using namespace Common;
using namespace Physic;
using namespace std;

GameEngineImpl::GameEngineImpl(const LevelDefinition &level, unsigned int playerCount) :
    m_gameState(level, playerCount, m_playerIds, m_wallids),
    m_grid(new Grid(level.getLevelHeight(), level.getLevelWidth())),
    m_firstGameStateUpdate(true),
    m_simulator(new GamePhysicSimulator(level))
{
    vector<const WallState*> walls = m_gameState.getAllChangedWalls();

    for (vector<const WallState*>::const_iterator i = walls.begin(); i != walls.end(); ++i)
        m_grid->addWallAtPlace(**i);

    for (unsigned int i = 0; i < playerCount; ++i)
        m_inputStates.insert(pair<unsigned int, InputState>(i, InputState()));
}

GameEngineImpl::~GameEngineImpl()
{
    delete m_grid;
    delete m_simulator;
}

void GameEngineImpl::updateGameState(const std::map<unsigned int, Common::InputState> &inputStates, double time)
{
    assert(m_inputStates.size() == inputStates.size());
    m_inputStates = inputStates;
    m_elapsedTime = time;

    if (!m_firstGameStateUpdate)
        m_gameState.resetChangedFlags();
    removeAllObjectsWithDestroyedFlagFromGrid();
    m_gameState.removeAllObjectsWithDestroyedFlag();
    playerGetsPowerUp();
    updateBombs();
    updatePlayerPositions();
    placeBombs();
    m_simulator->updateItems(m_gameState);

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

vector<unsigned int> GameEngineImpl::getAllPossiblePlayerIDs() const
{
    return m_gameState.getAllPossiblePlayerIDs();
}

void GameEngineImpl::updatePlayerVelocity(PlayerState &player, const InputState &input)
{
    if (input.isMoreThanOneMovementButtonPressed())
        setPlayerSpeedIfMoreThanOneDirectionIsSelected(player, input);
    else if (input.isMovementButtonPressed())
        setPlayerSpeedIntoOnlySelectedDirection(player, input);
    else
        setPlayerSpeedToNull(player);
}

void GameEngineImpl::updatePlayerWithBombCollisions()
{
    vector<unsigned int> playerIDs = m_gameState.getAllPossiblePlayerIDs();

    for (vector<unsigned int>::const_iterator i = playerIDs.begin(); i != playerIDs.end(); ++i)
    {
        PlayerState &player = m_gameState.getPlayerStateById(*i);
        vector<GridPoint> playerFields = m_grid->getPlayerFields(player);
        vector<const BombState*> bombsNotToCollideWith = player.getBombsNotToCollideWith();

        for (vector<const BombState*>::const_iterator j = bombsNotToCollideWith.begin(); j != bombsNotToCollideWith.end(); ++j)
        {
            GridPoint gridPosition((*j)->getPosition());

            if (count(playerFields.begin(), playerFields.end(), gridPosition) == 0)
                player.removeBombFromDoNotCollideList(*j);
        }
    }
}

void GameEngineImpl::updatePlayerPositions()
{
    updatePlayerVelocities();
    double realSimulatedTime = 0;
    double timeTillOnePlayerReachesGridPoint = getTimeTillOnePlayerReachesGridPoint();

    do
    {
        if (realSimulatedTime + timeTillOnePlayerReachesGridPoint < m_elapsedTime)
        {
            m_simulator->simulateStep(m_gameState, timeTillOnePlayerReachesGridPoint);
            realSimulatedTime += timeTillOnePlayerReachesGridPoint;
            updatePlayerVelocities();
        }

        timeTillOnePlayerReachesGridPoint = getTimeTillOnePlayerReachesGridPoint();
    } while (realSimulatedTime + timeTillOnePlayerReachesGridPoint < m_elapsedTime);

    m_simulator->simulateStep(m_gameState, m_elapsedTime - realSimulatedTime);

    updatePlayerWithBombCollisions();
}

void GameEngineImpl::updatePlayerVelocities()
{
    vector<unsigned int> playerIDs = m_gameState.getAllPossiblePlayerIDs();

    for (vector<unsigned int>::const_iterator i = playerIDs.begin(); i != playerIDs.end(); ++i)
    {
        PlayerState &player = m_gameState.getPlayerStateById(*i);
        vector<GridPoint> playerFields = m_grid->getPlayerFields(player);

        if (playerFields.size() == 1)
        {
            updatePlayerVelocity(player, m_inputStates.at(*i));
            GridPoint gridPosition(player.getPosition());
            player.setPosition(gridPosition.getPointPosition());
        }
    }
}

void GameEngineImpl::setPlayerSpeedIfMoreThanOneDirectionIsSelected(PlayerState &player, const InputState &input)
{
    assert(input.isMoreThanOneMovementButtonPressed());
    assert(input.isMovementButtonPressed());

    if (input.isUpKeyPressed() && player.getDirection() == PlayerState::PlayerDirectionUp)
        player.setMoving();
    else if (input.isDownKeyPressed() && player.getDirection() == PlayerState::PlayerDirectionDown)
        player.setMoving();
    else if (input.isLeftKeyPressed() && player.getDirection() == PlayerState::PlayerDirectionLeft)
        player.setMoving();
    else if (input.isRightKeyPressed() && player.getDirection() == PlayerState::PlayerDirectionRight)
        player.setMoving();
}

void GameEngineImpl::setPlayerSpeedIntoOnlySelectedDirection(PlayerState &player, const InputState &input)
{
    assert(!input.isMoreThanOneMovementButtonPressed());
    assert(input.isMovementButtonPressed());

    if (input.isUpKeyPressed())
    {
        player.setDirectionUp();
        player.setMoving();
    }
    else if (input.isDownKeyPressed())
    {
        player.setDirectionDown();
        player.setMoving();
    }
    else if (input.isLeftKeyPressed())
    {
        player.setDirectionLeft();
        player.setMoving();
    }
    else if (input.isRightKeyPressed())
    {
        player.setDirectionRight();
        player.setMoving();
    }
}

void GameEngineImpl::setPlayerSpeedToNull(Common::PlayerState &player)
{
    player.setNotMoving();
}

double GameEngineImpl::getTimeTillOnePlayerReachesGridPoint() const
{
    vector<unsigned int> playerIDs = m_gameState.getAllPossiblePlayerIDs();
    double minimalTime = numeric_limits<double>::max();

    for (vector<unsigned int>::const_iterator i = playerIDs.begin(); i != playerIDs.end(); ++i)
    {
        const PlayerState &player = m_gameState.getPlayerStateById(*i);
        double timeForOnePlayer = getTimeTillPlayerReachesGridPoint(player);
        minimalTime = min(minimalTime, timeForOnePlayer);
    }

    return minimalTime;
}

double GameEngineImpl::getTimeTillPlayerReachesGridPoint(const PlayerState &player) const
{
    double velocityX = player.getSpeedIntoX();
    double velocityY = player.getSpeedIntoY();
    const Point &position = player.getPosition();
    const GridPoint gridPosition(position);
    double time = 0;

    if (velocityX != 0)
    {
        double positionX = position.getX();
        unsigned int gridPositionX = gridPosition.getX();

        //! @todo replace with fuzzy
        if (fabs(gridPositionX - positionX) < 0.05)
            time = 1/fabs(velocityX);
        else
        {
            if (velocityX > 0)
                time = (positionX - gridPositionX)/velocityX;
            else
                time = (positionX - (gridPositionX + 1))/velocityX;
        }
    }

    if (velocityY != 0)
    {
        double positionY = position.getY();
        unsigned int gridPositionY = gridPosition.getY();

        //! @todo replace with fuzzy
        if (fabs(gridPositionY - positionY) < 0.05)
            time = 1/fabs(velocityY);
        else
        {
            if (velocityY > 0)
                time = (positionY - gridPositionY)/velocityY;
            else
                time = (positionY - (gridPositionY + 1))/velocityY;
        }
    }

    if (player.isMoving())
        return max(0.0, time);
    else
        return numeric_limits<double>::max()/2;
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

        vector<unsigned int> playersInRange;
        playersInRange = m_grid->getPlayersInRange(bomb);
        for(size_t j = 0; j < playersInRange.size(); j++)
            m_gameState.erasePlayerById(playersInRange[j]);
    }

    vector<const BombState*> destroyedBombs = m_gameState.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();

    for (vector<const BombState*>::const_iterator i = destroyedBombs.begin(); i != destroyedBombs.end(); ++i)
    {
        unsigned int playerID = (*i)->getPlayerID();
        PlayerState &player = m_gameState.getPlayerStateById(playerID);
        player.reduceBombCount();
        player.removeBombFromDoNotCollideList(*i);
    }
}

void GameEngineImpl::placeBombs()
{
    vector<unsigned int> playerIDs = m_gameState.getAllPossiblePlayerIDs();

    for (vector<unsigned int>::const_iterator i = playerIDs.begin(); i != playerIDs.end(); ++i)
    {
        PlayerState &player = m_gameState.getPlayerStateById(*i);
        const InputState &input = m_inputStates.at(*i);
        placeBombForPlayer(player, input);
    }
}

void GameEngineImpl::placeBombForPlayer(PlayerState &player, const InputState &input)
{
    if (input.isSpaceKeyPressed() && player.canPlayerPlaceBomb())
    {
        if(m_grid->isPlaceEmpty(player.getCenterPosition()))
        {
            BombState *bombPlaced = new BombState(m_bombids, player.getId());
            bombPlaced->setPosition(player.getCenterPosition());
            m_grid->addBombAtPlace(*bombPlaced);
            player.countBomb();
            player.doNotCollideWith(bombPlaced);
            m_gameState.addBomb(bombPlaced);
        }
    }
}

void GameEngineImpl::playerGetsPowerUp()
{
    vector<unsigned int> playerIDs = m_gameState.getAllPossiblePlayerIDs();
    vector<unsigned int> powerUpIDs = m_gameState.getAllPossiblePowerUpIDs();

    for (vector<unsigned int>::const_iterator i = playerIDs.begin(); i != playerIDs.end(); ++i)
    {
        PlayerState &player = m_gameState.getPlayerStateById(*i);
        vector<GridPoint> playerFields = m_grid->getPlayerFields(player);
        if(playerFields.size() == 1)
        {
        for(vector<unsigned int>::const_iterator j = powerUpIDs.begin(); j != powerUpIDs.end(); ++j)
            {
            const PowerUpState *powerup = m_gameState.getPowerUpById(*j);
            const Point powerUpPosition = powerup->getPosition();
            GridPoint powerUpField(powerUpPosition);
            if(powerUpField==playerFields[0])
                {
                powerup->modifyPlayer(player);
                m_gameState.erasePowerUpById(*j);
                }
            }

        }
    }
}

void GameEngineImpl::addPowerUp(PowerUpState* powerUp)
{
    m_gameState.addPowerUp(powerUp);
    m_grid->addPowerUpAtPlace(*powerUp);
}

void GameEngineImpl::addRandomPowerUpAtPosition(Point position)
{
    PowerUpGenerator generator;
    PowerUpType randomType = generator.getRandomPowerUpType();

    if (randomType == PowerUpTypeNone)
            return;
    else if (randomType == PowerUpTypeMaxBomb)
    {
        PowerUpMaxBombState *powerUp = new PowerUpMaxBombState(m_powerUpIds, position);
        addPowerUp(powerUp);
    }
    else if (randomType == PowerUpTypeMaxVelocity)
    {
        PowerUpMaxVelocityState *powerUp = new PowerUpMaxVelocityState(m_powerUpIds, position);
        addPowerUp(powerUp);
    }
    else
        assert(false);


}

void GameEngineImpl::removeAllObjectsWithDestroyedFlagFromGrid()
{
    vector<const BombState*> allBombsWithDestroyedFlag = m_gameState.getAllBombsWithDestroyedFlag();
    for(size_t i = 0;i < allBombsWithDestroyedFlag.size();i++)
        m_grid->removeBomb(*allBombsWithDestroyedFlag[i]);

    vector<const WallState*> allWallsWithDestroyedFlag = m_gameState.getAllWallsWithDestroyedFlag();
    for(size_t i = 0;i < allWallsWithDestroyedFlag.size();i++)
    {
        Point position;
        position = allWallsWithDestroyedFlag[i]->getPosition();
        m_grid->removeWall(*allWallsWithDestroyedFlag[i]);
        addRandomPowerUpAtPosition(position);

    }

    vector<const PowerUpState*> allPowerUpsWithDestroyedFlag = m_gameState.getAllPowerUpsWithDestroyedFlag();
    for(size_t i = 0;i < allPowerUpsWithDestroyedFlag.size();i++)
        m_grid->removePowerUp(*allPowerUpsWithDestroyedFlag[i]);
}

