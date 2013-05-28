#include "gamestatetest.h"
#include "gamestate.h"
#include "uniqueidcreator.h"

using namespace Common;
using namespace std;

void GameStateTest::addWall_defaultWall_wallCountIs1()
{
    UniqueIdCreator id;
	GameState m_state;
    m_state.addWall(new WallState(id));

    vector<WallState*> walls = m_state.getAllWalls();
	CPPUNIT_ASSERT_EQUAL((size_t)1, walls.size());
}

void GameStateTest::addBomb_defaultBomb_bombCountIs1()
{
    UniqueIdCreator id;
	GameState m_state;
    m_state.addBomb(new BombState(id));

    vector<BombState*> bombs = m_state.getAllBombs();
	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}

void GameStateTest::eraseBomb_defaultBomb_bombCountIs1()
{
    UniqueIdCreator id;
    GameState m_state;
    m_state.addBomb(new BombState(id));
    m_state.addBomb(new BombState(id));
    m_state.eraseBomb(1);

    vector<BombState*> bombs = m_state.getAllBombs();
    CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}
