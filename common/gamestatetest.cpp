#include "gamestatetest.h"
#include "gamestate.h"
#include "uniqueidcreator.h"

using namespace Common;
using namespace std;

void GameStateTest::addWall_defaultWall_wallCountIs1()
{
	UniqueIdCreator id;
	GameState state;

    state.addWall(new WallState(id, WallState::WallTypeSolid));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getWallCount());
}

void GameStateTest::addBomb_defaultBomb_bombCountIs1()
{
	UniqueIdCreator id;
	GameState state;

	state.addBomb(new BombState(id));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getBombCount());
}

void GameStateTest::eraseBomb_defaultBomb_bombCountIs1()
{
	UniqueIdCreator id;
	GameState state;
	state.addBomb(new BombState(id));
	state.addBomb(new BombState(id));
	state.eraseBomb(1);

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getBombCount());
}

void GameStateTest::getAllChangedBombs_twoBombsAdded_resultSizeIs2()
{
	UniqueIdCreator id;
	GameState state;
	state.addBomb(new BombState(id));
	state.addBomb(new BombState(id));

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)2, bombs.size());
}

void GameStateTest::getAllChangedWalls_twoWallsAdded_resultSizeIs2()
{
	UniqueIdCreator id;
	GameState state;
    state.addWall(new WallState(id, WallState::WallTypeSolid));
    state.addWall(new WallState(id, WallState::WallTypeSolid));

	vector<const WallState*> walls = state.getAllChangedWalls();

	CPPUNIT_ASSERT_EQUAL((size_t)2, walls.size());
}

void GameStateTest::getAllBombsLifeTime_AfterReduceLifeTime_resultTimeIs2()
{
    UniqueIdCreator id;
    GameState state;
    const BombState* bomb;
    state.addBomb(new BombState(id));
    state.reduceAllBombsLifeTime(1);

    vector<const BombState*> bombs = state.getAllChangedBombs();
    bomb = bombs[0];

    CPPUNIT_ASSERT_EQUAL((double)2, bomb->getLifeTime());
}
