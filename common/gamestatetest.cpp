#include "gamestatetest.h"
#include "gamestate.h"
#include "uniqueidcreator.h"

using namespace Common;
using namespace std;

void GameStateTest::addWall_defaultWall_wallCountIs1()
{
	UniqueIdCreator id;
	GameState state;
	state.addWall(new WallState(id));

	vector<WallState*> walls = state.getAllWalls();
	CPPUNIT_ASSERT_EQUAL((size_t)1, walls.size());
}

void GameStateTest::addBomb_defaultBomb_bombCountIs1()
{
	UniqueIdCreator id;
	GameState state;
	state.addBomb(new BombState(id));

	vector<BombState*> bombs = state.getAllBombs();
	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}

void GameStateTest::eraseBomb_defaultBomb_bombCountIs1()
{
	UniqueIdCreator id;
	GameState state;
	state.addBomb(new BombState(id));
	state.addBomb(new BombState(id));
	state.eraseBomb(1);

	vector<BombState*> bombs = state.getAllBombs();
	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}

void GameStateTest::getAllChangedWalls_twoWallsAdded_resultSizeIs2()
{
	UniqueIdCreator id;
	GameState state;
	state.addBomb(new BombState(id));
	state.addBomb(new BombState(id));

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)2, bombs.size());
}

void GameStateTest::getAllChangedBombs_twoBombsAdded_resultSizeIs2()
{
	UniqueIdCreator id;
	GameState state;
	state.addWall(new WallState(id));
	state.addWall(new WallState(id));

	vector<const WallState*> walls = state.getAllChangedWalls();

	CPPUNIT_ASSERT_EQUAL((size_t)2, walls.size());
}
