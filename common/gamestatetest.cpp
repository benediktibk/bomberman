#include "gamestatetest.h"
#include "gamestate.h"
#include "uniqueidcreator.h"

using namespace Common;
using namespace std;

void GameStateTest::addWall_defaultWall_wallCountIs1()
{
	UniqueIdCreator idCreator;
	GameState state;

	state.addWall(new WallState(idCreator, WallState::WallTypeSolid, Point()));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getWallCount());
}

void GameStateTest::addBomb_defaultBomb_bombCountIs1()
{
	UniqueIdCreator idCreator;
	GameState state;

	state.addBomb(new BombState(idCreator));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getBombCount());
}

void GameStateTest::getAllChangedBombs_twoBombsAdded_resultSizeIs2()
{
	UniqueIdCreator idCreator;
	GameState state;
	state.addBomb(new BombState(idCreator));
	state.addBomb(new BombState(idCreator));

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)2, bombs.size());
}

void GameStateTest::getAllChangedWalls_twoWallsAdded_resultSizeIs2()
{
	UniqueIdCreator idCreator;
	GameState state;
	state.addWall(new WallState(idCreator, WallState::WallTypeSolid, Point()));
	state.addWall(new WallState(idCreator, WallState::WallTypeSolid, Point()));

	vector<const WallState*> walls = state.getAllChangedWalls();

	CPPUNIT_ASSERT_EQUAL((size_t)2, walls.size());
}

void GameStateTest::getAllBombsLifeTime_AfterReduceLifeTime_resultTimeIs2()
{
	UniqueIdCreator idCreator;
	GameState state;
	const BombState* bomb;
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(1);

	vector<const BombState*> bombs = state.getAllChangedBombs();
	bomb = bombs[0];

	CPPUNIT_ASSERT_EQUAL((double)2, bomb->getLifeTime());
}

void GameStateTest::getAllChangedBombs_twoBombsAddedAndOneDeleted_resultSizeIs1()
{
	UniqueIdCreator idCreator;
	GameState state;
	PlayerState playerState;

	playerState.countBomb();
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(1);
	playerState.countBomb();
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(2.1);
	state.deleteAllBombsWithNegativeLifeTime(playerState);

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}

void GameStateTest::getAllChangedBombs_twoBombsAddedAndOneDeleted_resultBombCountIs1()
{
	UniqueIdCreator idCreator;
	GameState state;
	PlayerState playerState;

	playerState.countBomb();
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(1);
	playerState.countBomb();
	state.addBomb(new BombState(idCreator));
	state.reduceAllBombsLifeTime(2.1);
	state.deleteAllBombsWithNegativeLifeTime(playerState);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, playerState.getBombCount());
}
