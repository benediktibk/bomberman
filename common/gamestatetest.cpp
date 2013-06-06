#include "gamestatetest.h"
#include "gamestate.h"

using namespace Common;
using namespace std;

void GameStateTest::addWall_defaultWall_wallCountIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);

	state.addWall(new WallState(m_wallIDCreator, WallState::WallTypeSolid, Point()));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getWallCount());
}

void GameStateTest::addBomb_defaultBomb_bombCountIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);

	state.addBomb(new BombState(m_bombIDCreator));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getBombCount());
}

void GameStateTest::getAllChangedBombs_twoBombsAdded_resultSizeIs2()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.addBomb(new BombState(m_bombIDCreator));
	state.addBomb(new BombState(m_bombIDCreator));

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)2, bombs.size());
}

void GameStateTest::getAllChangedBombs_oneBombAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.addBomb(new BombState(m_bombIDCreator));
	state.resetChangedFlags();
	state.addBomb(new BombState(m_bombIDCreator));

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}

void GameStateTest::getAllChangedWalls_twoWallsAdded_resultSizeIs2()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.addWall(new WallState(m_wallIDCreator, WallState::WallTypeSolid, Point()));
	state.addWall(new WallState(m_wallIDCreator, WallState::WallTypeSolid, Point()));

	vector<const WallState*> walls = state.getAllChangedWalls();

	CPPUNIT_ASSERT_EQUAL((size_t)2, walls.size());
}

void GameStateTest::getAllChangedWalls_oneWallAdedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.addWall(new WallState(m_wallIDCreator, WallState::WallTypeSolid, Point()));
	state.resetChangedFlags();
	state.addWall(new WallState(m_wallIDCreator, WallState::WallTypeSolid, Point()));

	vector<const WallState*> walls = state.getAllChangedWalls();

	CPPUNIT_ASSERT_EQUAL((size_t)1, walls.size());
}

void GameStateTest::getAllBombsLifeTime_afterReduceLifeTime_resultTimeIs2()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	const BombState* bomb;
	state.addBomb(new BombState(m_bombIDCreator));
	state.reduceAllBombsLifeTime(1);
	state.removeAllObjectsWithDestroyedFlag();

	vector<const BombState*> bombs = state.getAllChangedBombs();
	bomb = bombs[0];

	CPPUNIT_ASSERT_EQUAL((double)2, bomb->getLifeTime());
}

void GameStateTest::getAllChangedBombs_twoBombsAddedAndOneDeleted_resultSizeIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	PlayerState &playerState = state.getFirstPlayerState();

	playerState.countBomb();
	state.addBomb(new BombState(m_bombIDCreator));
	state.reduceAllBombsLifeTime(1);
	playerState.countBomb();
	state.addBomb(new BombState(m_bombIDCreator));
	state.reduceAllBombsLifeTime(2.1);
	state.setAllBombsWithNoLifeTimeDestroyed(playerState);
	state.removeAllObjectsWithDestroyedFlag();

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}

void GameStateTest::getAllChangedBombs_twoBombsAddedAndOneDeleted_bombCountIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	PlayerState &playerState = state.getFirstPlayerState();

	playerState.countBomb();
	state.addBomb(new BombState(m_bombIDCreator));
	state.reduceAllBombsLifeTime(1);
	playerState.countBomb();
	state.addBomb(new BombState(m_bombIDCreator));
	state.reduceAllBombsLifeTime(2.1);
	state.setAllBombsWithNoLifeTimeDestroyed(playerState);
	state.removeAllObjectsWithDestroyedFlag();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, playerState.getBombCount());
}

void GameStateTest::resetChangedFlags_oneWallAdded_wallIsNotChanged()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	WallState *wall = new WallState(m_wallIDCreator, WallState::WallTypeSolid, Point());
	state.addWall(wall);

	state.resetChangedFlags();

	CPPUNIT_ASSERT(!wall->hasChanged());
}

void GameStateTest::resetChangedFlags_oneBombAdded_bombIsNotChanged()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	BombState *bomb = new BombState(m_bombIDCreator);
	state.addBomb(bomb);

	state.resetChangedFlags();

	CPPUNIT_ASSERT(!bomb->hasChanged());
}

void GameStateTest::getHeight_heightLevelDefinition_resultIs50()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);

	CPPUNIT_ASSERT_EQUAL(level.getLevelHeight(), state.getGameStateHeight());
}

void GameStateTest::getWidth_widthLevelDefinition_resultIs50()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);

	CPPUNIT_ASSERT_EQUAL(level.getLevelWidth(), state.getGameStateWidth());
}

void GameStateTest::getAllBombsWithNegativeLifeTime_twoBombsAddedOneWithNegativeTime_resultSizeIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	const BombState* bomb;
	state.addBomb(new BombState(m_bombIDCreator));
	state.reduceAllBombsLifeTime(2);
	state.addBomb(new BombState(m_bombIDCreator));
	state.reduceAllBombsLifeTime(2);

	vector<const BombState*> bombs = state.getAllChangedBombs();
	bomb = bombs[0];

	CPPUNIT_ASSERT_EQUAL((-1.0), bomb->getLifeTime());
}

void GameStateTest::eraseWallById_twoWallsAddedOneDeleted_wallCountIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.addWall(new WallState(m_wallIDCreator, WallState::WallTypeLoose, Point()));
	state.addWall(new WallState(m_wallIDCreator, WallState::WallTypeLoose, Point()));
	state.eraseWallById(1);
	state.removeAllObjectsWithDestroyedFlag();

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getWallCount());
}

void GameStateTest::setBombsLifeTimeToZero_oneBombAddedAndSetLifeTimeZero_lifeTimeIs0()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	const BombState* bomb;
	state.addBomb(new BombState(m_bombIDCreator));
	state.setBombsLifeTimeToZero(0);

	vector<const BombState*> bombs = state.getAllChangedBombs();
	bomb = bombs[0];

	CPPUNIT_ASSERT_EQUAL((0.0), bomb->getLifeTime());
}

void GameStateTest::addPowerUp_defaultPowerUp_powerUpCountIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);

	state.addPowerUp(new PowerUpState(m_powerUpIDCreator, Point()));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getPowerUpCount());
}

void GameStateTest::getAllChangedPowerUps_twoPowerUpsAdded_resultSizeIs2()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.addPowerUp(new PowerUpState(m_powerUpIDCreator, Point()));
	state.addPowerUp(new PowerUpState(m_powerUpIDCreator, Point()));

	vector<const PowerUpState*> powerUps = state.getAllChangedPowerUps();

	CPPUNIT_ASSERT_EQUAL((size_t)2, powerUps.size());
}

void GameStateTest::removePowerUpById_twoPowerUpsAdddedOneDeleted_PowerUpCountIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.addPowerUp(new PowerUpState(m_powerUpIDCreator, Point()));
	state.addPowerUp(new PowerUpState(m_powerUpIDCreator, Point()));
	state.erasePowerUpById(1);
	state.removeAllObjectsWithDestroyedFlag();

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getPowerUpCount());

}

void GameStateTest::getAllChangedPowerUps_onePowerUpAdedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.addPowerUp(new PowerUpState(m_powerUpIDCreator, Point()));
	state.resetChangedFlags();
	state.addPowerUp(new PowerUpState(m_powerUpIDCreator, Point()));

	vector<const PowerUpState*> powerUps = state.getAllChangedPowerUps();

	CPPUNIT_ASSERT_EQUAL((size_t)1, powerUps.size());
}

void GameStateTest::resetChangedFlags_onePowerUpAdded_powerUpIsNotChanged()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	PowerUpState *powerUp = new PowerUpState(m_powerUpIDCreator, Point());
	state.addPowerUp(powerUp);

	state.resetChangedFlags();

	CPPUNIT_ASSERT(!powerUp->hasChanged());
}

void GameStateTest::getAllPossiblePlayerIDs_onePlayerCreated_resultSizeIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);

	vector<unsigned int> playerIDs = state.getAllPossiblePlayerIDs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, playerIDs.size());
}

void GameStateTest::constructor_3players_playerCountIs3()
{
	LevelDefinition level;
	GameState state(level, 3, m_playerIDCreator, m_wallIDCreator);

	const vector<const PlayerState*> &players = state.getAllPlayers();

	CPPUNIT_ASSERT_EQUAL((size_t)3, players.size());
}
