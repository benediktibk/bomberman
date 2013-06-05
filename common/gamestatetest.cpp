#include "gamestatetest.h"
#include "gamestate.h"
#include "uniqueidcreator.h"

using namespace Common;
using namespace std;

void GameStateTest::addWall_defaultWall_wallCountIs1()
{
	UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);

	state.addWall(new WallState(idCreator, WallState::WallTypeSolid, Point()));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getWallCount());
}

void GameStateTest::addBomb_defaultBomb_bombCountIs1()
{
	UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);

	state.addBomb(new BombState(idCreator));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getBombCount());
}

void GameStateTest::getAllChangedBombs_twoBombsAdded_resultSizeIs2()
{
	UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
	state.addBomb(new BombState(idCreator));
	state.addBomb(new BombState(idCreator));

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)2, bombs.size());
}

void GameStateTest::getAllChangedBombs_oneBombAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1()
{
	UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
	state.addBomb(new BombState(idCreator));
	state.resetChangedFlags();
	state.addBomb(new BombState(idCreator));

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}

void GameStateTest::getAllChangedWalls_twoWallsAdded_resultSizeIs2()
{
	UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
	state.addWall(new WallState(idCreator, WallState::WallTypeSolid, Point()));
	state.addWall(new WallState(idCreator, WallState::WallTypeSolid, Point()));

	vector<const WallState*> walls = state.getAllChangedWalls();

	CPPUNIT_ASSERT_EQUAL((size_t)2, walls.size());
}

void GameStateTest::getAllChangedWalls_oneWallAdedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1()
{
	UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
	state.addWall(new WallState(idCreator, WallState::WallTypeSolid, Point()));
	state.resetChangedFlags();
	state.addWall(new WallState(idCreator, WallState::WallTypeSolid, Point()));

	vector<const WallState*> walls = state.getAllChangedWalls();

	CPPUNIT_ASSERT_EQUAL((size_t)1, walls.size());
}

void GameStateTest::getAllBombsLifeTime_afterReduceLifeTime_resultTimeIs2()
{
    UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
	const BombState* bomb;
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(1);
	state.removeAllObjectsWithDestroyedFlag();

	vector<const BombState*> bombs = state.getAllChangedBombs();
	bomb = bombs[0];

	CPPUNIT_ASSERT_EQUAL((double)2, bomb->getLifeTime());
}

void GameStateTest::getAllChangedBombs_twoBombsAddedAndOneDeleted_resultSizeIs1()
{
    UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
    PlayerState &playerState = state.getPlayerState();

	playerState.countBomb();
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(1);
	playerState.countBomb();
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(2.1);
	state.setAllBombsWithNoLifeTimeDestroyed(playerState);
	state.removeAllObjectsWithDestroyedFlag();

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}

void GameStateTest::getAllChangedBombs_twoBombsAddedAndOneDeleted_bombCountIs1()
{
    UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
    PlayerState &playerState = state.getPlayerState();

	playerState.countBomb();
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(1);
	playerState.countBomb();
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(2.1);
	state.setAllBombsWithNoLifeTimeDestroyed(playerState);
	state.removeAllObjectsWithDestroyedFlag();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, playerState.getBombCount());
}

void GameStateTest::resetChangedFlags_oneWallAdded_wallIsNotChanged()
{
	UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
	WallState *wall = new WallState(idCreator, WallState::WallTypeSolid, Point());
	state.addWall(wall);

	state.resetChangedFlags();

	CPPUNIT_ASSERT(!wall->hasChanged());
}

void GameStateTest::resetChangedFlags_oneBombAdded_bombIsNotChanged()
{
	UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
	BombState *bomb = new BombState(idCreator);
	state.addBomb(bomb);

	state.resetChangedFlags();

	CPPUNIT_ASSERT(!bomb->hasChanged());
}

void GameStateTest::getHeight_heightLevelDefinition_resultIs50()
{
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);

    CPPUNIT_ASSERT_EQUAL(level.getLevelHeight(), state.getGameStateHeight());
}

void GameStateTest::getWidth_widthLevelDefinition_resultIs50()
{
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);

    CPPUNIT_ASSERT_EQUAL(level.getLevelWidth(), state.getGameStateWidth());
}

void GameStateTest::getAllBombsWithNegativeLifeTime_twoBombsAddedOneWithNegativeTime_resultSizeIs1()
{
    UniqueIdCreator idPlayer;
    UniqueIdCreator idCreator;
    LevelDefinition level;
    GameState state(level,idPlayer);
	const BombState* bomb;
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(2);
    state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(2);

	vector<const BombState*> bombs = state.getAllChangedBombs();
	bomb = bombs[0];

	CPPUNIT_ASSERT_EQUAL((-1.0), bomb->getLifeTime());
}

void GameStateTest::eraseWallById_twoWallsAddedOneDeleted_wallCountIs1()
{
	UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
	state.addWall(new WallState(idCreator, WallState::WallTypeLoose, Point()));
	state.addWall(new WallState(idCreator, WallState::WallTypeLoose, Point()));
    state.eraseWallById(1);
    state.removeAllObjectsWithDestroyedFlag();

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getWallCount());
}


void GameStateTest::setBombsLifeTimeToZero_oneBombAddedAndSetLifeTimeZero_lifeTimeIs0()
{
    UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);
	const BombState* bomb;
	state.addBomb(new BombState(idCreator));
    state.setBombsLifeTimeToZero(0);
    
	vector<const BombState*> bombs = state.getAllChangedBombs();
	bomb = bombs[0];

	CPPUNIT_ASSERT_EQUAL((0.0), bomb->getLifeTime());
}

void GameStateTest::addPowerUp_defaultPowerUp_powerUpCountIs1()
{
	UniqueIdCreator idCreator;
    UniqueIdCreator idPlayer;
    LevelDefinition level;
    GameState state(level,idPlayer);

    state.addPowerUp(new PowerUpState(idCreator,Point()));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getPowerUpCount());
}
