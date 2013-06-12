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

	state.addBomb(new BombState(m_bombIDCreator, 0));

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getBombCount());
}

void GameStateTest::getAllChangedBombs_twoBombsAdded_resultSizeIs2()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.addBomb(new BombState(m_bombIDCreator, 0));
	state.addBomb(new BombState(m_bombIDCreator, 0));

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)2, bombs.size());
}

void GameStateTest::getAllChangedBombs_oneBombAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.addBomb(new BombState(m_bombIDCreator, 0));
	state.resetChangedFlags();
	state.addBomb(new BombState(m_bombIDCreator, 0));

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}

void GameStateTest::getAllChangedExplodedBombs_oneExplodedBombAdded_resultSizeIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	BombState *bomb = new BombState(m_bombIDCreator, 0);
	state.addBomb(bomb);
	state.reduceAllBombsLifeTime(bomb->getLifeTime()*2);
	state.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();

	vector<const ExplodedBombState*> explodedBombs = state.getAllChangedExplodedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, explodedBombs.size());
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

void GameStateTest::getAllChangedWalls_oneWallAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1()
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
	state.addBomb(new BombState(m_bombIDCreator, 0));
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
	state.addBomb(new BombState(m_bombIDCreator, 0));
	state.reduceAllBombsLifeTime(1);
	playerState.countBomb();
	state.addBomb(new BombState(m_bombIDCreator, 0));
	state.reduceAllBombsLifeTime(2.1);
	state.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();
	state.removeAllObjectsWithDestroyedFlag();

	vector<const BombState*> bombs = state.getAllChangedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
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
	BombState *bomb = new BombState(m_bombIDCreator, 0);
	state.addBomb(bomb);

	state.resetChangedFlags();

	CPPUNIT_ASSERT(!bomb->hasChanged());
}

void GameStateTest::getHeight_heightLevelDefinition_resultIs50()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);

	CPPUNIT_ASSERT_EQUAL(level.getLevelHeight(), state.getHeight());
}

void GameStateTest::getWidth_widthLevelDefinition_resultIs50()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);

	CPPUNIT_ASSERT_EQUAL(level.getLevelWidth(), state.getWidth());
}

void GameStateTest::getAllBombsWithNegativeLifeTime_twoBombsAddedOneWithNegativeTime_resultSizeIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	const BombState* bomb;
	state.addBomb(new BombState(m_bombIDCreator, 0));
	state.reduceAllBombsLifeTime(2);
	state.addBomb(new BombState(m_bombIDCreator, 0));
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
	state.addBomb(new BombState(m_bombIDCreator, 0));
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

void GameStateTest::resetChangedFlags_oneExplodedBombAdded_noChangedExplodedBombs()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	BombState *bomb = new BombState(m_bombIDCreator, 0);
	state.addBomb(bomb);
	state.reduceAllBombsLifeTime(bomb->getLifeTime()*2);
	state.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();

	state.resetChangedFlags();

	vector<const ExplodedBombState*> explodedBombs = state.getAllChangedExplodedBombs();
	CPPUNIT_ASSERT_EQUAL((size_t)0, explodedBombs.size());
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
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 0);
	GameState state(level, 3, m_playerIDCreator, m_wallIDCreator);

	const vector<const PlayerState*> &players = state.getAllPlayers();

	CPPUNIT_ASSERT_EQUAL((size_t)3, players.size());
}

void GameStateTest::constructor_threePlayersOnDifferentPositions_allPlayersHaveDifferentPositions()
{
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 2);
	GameState state(level, 3, m_playerIDCreator, m_wallIDCreator);

	const vector<const PlayerState*> &players = state.getAllPlayers();

	Point firstPosition(players[0]->getPosition());
	Point secondPosition(players[1]->getPosition());
	Point thirdPosition(players[2]->getPosition());
	CPPUNIT_ASSERT(!firstPosition.fuzzyEqual(secondPosition, 0.001));
	CPPUNIT_ASSERT(!firstPosition.fuzzyEqual(thirdPosition, 0.001));
	CPPUNIT_ASSERT(!secondPosition.fuzzyEqual(thirdPosition, 0.001));
}

void GameStateTest::setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_oneBombWithNoLifeTime_resultSizeIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	BombState *bomb = new BombState(m_bombIDCreator, 0);
	state.addBomb(bomb);
	state.reduceAllBombsLifeTime(bomb->getLifeTime()*2);

	vector<const BombState*> result = state.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, result.size());
}

void GameStateTest::setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_oneBombWithNoLifeTime_resultIsAddedBomb()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	BombState *bomb = new BombState(m_bombIDCreator, 0);
	state.addBomb(bomb);
	state.reduceAllBombsLifeTime(bomb->getLifeTime()*2);

	vector<const BombState*> result = state.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();

	CPPUNIT_ASSERT(bomb == result.front());
}

void GameStateTest::setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_twoOfThreeBombsWithNoLifeTime_resultSizeIs2()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	BombState *bomb = new BombState(m_bombIDCreator, 0);
	state.addBomb(bomb);
	state.addBomb(new BombState(m_bombIDCreator, 0));
	state.reduceAllBombsLifeTime(bomb->getLifeTime()*2);
	state.addBomb(new BombState(m_bombIDCreator, 0));

	vector<const BombState*> result = state.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void GameStateTest::setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_oneBombWithNoLifeTime_explodedBombCountIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	BombState *bomb = new BombState(m_bombIDCreator, 0);
	state.addBomb(bomb);
	state.reduceAllBombsLifeTime(bomb->getLifeTime()*2);

	state.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();

	CPPUNIT_ASSERT_EQUAL((size_t)1, state.getExplodedBombCount());
}

void GameStateTest::erasePlayerById_onePlayersAddedOneDeleted_playerCountIs0()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	state.erasePlayerById(0);
	state.removeAllObjectsWithDestroyedFlag();

	CPPUNIT_ASSERT_EQUAL((size_t)0, state.getPlayerCount());
}

void GameStateTest::getAllBombsWithDestroyedFlag_twoBombsAddedOneDestroyed_resultIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	PlayerState &playerState = state.getFirstPlayerState();

	playerState.countBomb();
	state.addBomb(new BombState(m_bombIDCreator, 0));
	state.reduceAllBombsLifeTime(1);
	playerState.countBomb();
	state.addBomb(new BombState(m_bombIDCreator, 0));
	state.reduceAllBombsLifeTime(2.1);
	state.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();

	vector<const BombState*> bombs = state.getAllBombsWithDestroyedFlag();

	CPPUNIT_ASSERT_EQUAL((size_t)1, bombs.size());
}

void GameStateTest::getAllWallsWithDestroyedFlag_twoWallsAddedOneDestroyed_resultIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);

	state.addWall(new WallState(m_wallIDCreator, WallState::WallTypeLoose, Point()));
	state.addWall(new WallState(m_wallIDCreator, WallState::WallTypeLoose, Point()));
	state.eraseWallById(0);

	vector<const WallState*> walls = state.getAllWallsWithDestroyedFlag();

	CPPUNIT_ASSERT_EQUAL((size_t)1, walls.size());
}

void GameStateTest::getAllPowerUpsWithDestroyedFlag_twoPowerUpsAddedOneDestroyed_resultIs1()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);

	state.addPowerUp(new PowerUpState(m_powerUpIDCreator, Point()));
	state.addPowerUp(new PowerUpState(m_powerUpIDCreator, Point()));
	state.erasePowerUpById(0);

	vector<const PowerUpState*> powerUps = state.getAllPowerUpsWithDestroyedFlag();

	CPPUNIT_ASSERT_EQUAL((size_t)1, powerUps.size());
}

void GameStateTest::reduceAllBombsLifeTime_oneExplodedBomb_explodedBombsLifeTimeDecreased()
{
	LevelDefinition level;
	GameState state(level, 1, m_playerIDCreator, m_wallIDCreator);
	BombState *bomb = new BombState(m_bombIDCreator, 0);
	state.addBomb(bomb);
	state.reduceAllBombsLifeTime(bomb->getLifeTime()*2);
	state.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();
	state.reduceAllBombsLifeTime(0.7);

	vector<const ExplodedBombState*> explodedBombs = state.getAllChangedExplodedBombs();
	const ExplodedBombState &explodedBomb = *(explodedBombs.front());

	CPPUNIT_ASSERT_DOUBLES_EQUAL(ExplodedBombState::initialLifeTime() - 0.7, explodedBomb.getLifeTime(), 0.001);
}
