#include "gamestatetest.h"
#include "gamestate.h"

using namespace Common;
using namespace std;

void GameStateTest::addWall_defaultWall_wallCountIs1()
{
	GameState m_state;

	m_state.addWall(WallState());

	vector<WallState> walls = m_state.getAllWalls();
	CPPUNIT_ASSERT_EQUAL((size_t)1, walls.size());
}

void GameStateTest::addBomb_defaultBomb_bombCountIs1()
{
	GameState m_state;

	m_state.addBomb(BombState());

	vector<BombState> bombs = m_state.getAllBombs();
	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}