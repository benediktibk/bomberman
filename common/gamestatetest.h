#ifndef COMMON_GAMESTATETEST_H
#define COMMON_GAMESTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "uniqueidcreator.h"

namespace Common
{
	class GameStateTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(GameStateTest);
		 CPPUNIT_TEST(addWall_defaultWall_wallCountIs1);
		 CPPUNIT_TEST(addBomb_defaultBomb_bombCountIs1);
		 CPPUNIT_TEST(getAllChangedWalls_twoWallsAdded_resultSizeIs2);
		 CPPUNIT_TEST(getAllChangedWalls_oneWallAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1);
		 CPPUNIT_TEST(getAllChangedBombs_twoBombsAdded_resultSizeIs2);
		 CPPUNIT_TEST(getAllBombsLifeTime_afterReduceLifeTime_resultTimeIs2);
		 CPPUNIT_TEST(getAllChangedBombs_twoBombsAddedAndOneDeleted_resultSizeIs1);
		 CPPUNIT_TEST(getAllChangedBombs_oneBombAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1);
		 CPPUNIT_TEST(getAllChangedExplodedBombs_oneExplodedBombAdded_resultSizeIs1);
		 CPPUNIT_TEST(resetChangedFlags_oneWallAdded_wallIsNotChanged);
		 CPPUNIT_TEST(resetChangedFlags_oneBombAdded_bombIsNotChanged);
		 CPPUNIT_TEST(getHeight_heightLevelDefinition_resultIs50);
		 CPPUNIT_TEST(getWidth_widthLevelDefinition_resultIs50);
		 CPPUNIT_TEST(getAllBombsWithNegativeLifeTime_twoBombsAddedOneWithNegativeTime_resultSizeIs1);
		 CPPUNIT_TEST(eraseWallById_twoWallsAddedOneDeleted_wallCountIs1);
		 CPPUNIT_TEST(setBombsLifeTimeToZero_oneBombAddedAndSetLifeTimeZero_lifeTimeIs0);
		 CPPUNIT_TEST(addPowerUp_defaultPowerUp_powerUpCountIs1);
		 CPPUNIT_TEST(removePowerUpById_twoPowerUpsAdddedOneDeleted_PowerUpCountIs1);
		 CPPUNIT_TEST(getAllChangedPowerUps_twoPowerUpsAdded_resultSizeIs2);
		 CPPUNIT_TEST(getAllChangedPowerUps_onePowerUpAdedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1);
		 CPPUNIT_TEST(resetChangedFlags_onePowerUpAdded_powerUpIsNotChanged);
		 CPPUNIT_TEST(resetChangedFlags_oneExplodedBombAdded_noChangedExplodedBombs);
		 CPPUNIT_TEST(getAllNotDestroyedPlayerIDs_onePlayerCreated_resultSizeIs1);
		 CPPUNIT_TEST(constructor_3players_playerCountIs3);
		 CPPUNIT_TEST(constructor_threePlayersOnDifferentPositions_allPlayersHaveDifferentPositions);
		 CPPUNIT_TEST(setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_oneBombWithNoLifeTime_resultSizeIs1);
		 CPPUNIT_TEST(setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_oneBombWithNoLifeTime_resultIsAddedBomb);
		 CPPUNIT_TEST(setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_twoOfThreeBombsWithNoLifeTime_resultSizeIs2);
		 CPPUNIT_TEST(setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_oneBombWithNoLifeTime_explodedBombCountIs1);
		 CPPUNIT_TEST(getExplodedBombByBomb_oneExplodedBombWithDestructionRange3_destructionRangeIs3);
		 CPPUNIT_TEST(erasePlayerById_onePlayersAddedOneDeleted_playerCountIs0);
		 CPPUNIT_TEST(getAllBombsWithDestroyedFlag_twoBombsAddedOneDestroyed_resultIs1);
		 CPPUNIT_TEST(getAllWallsWithDestroyedFlag_twoWallsAddedOneDestroyed_resultIs1);
		 CPPUNIT_TEST(getAllPowerUpsWithDestroyedFlag_twoPowerUpsAddedOneDestroyed_resultIs1);
		 CPPUNIT_TEST(reduceAllBombsLifeTime_oneExplodedBomb_explodedBombsLifeTimeDecreased);
		 CPPUNIT_TEST(removeAllObjectsWithDestroyedFlag_oneDestroyedExplodedBomb_explodedBombCountIs0);
		 CPPUNIT_TEST(isPlayersAlive_OnePlayerNotDestroyed_resultIsTrue);
		 CPPUNIT_TEST(isPlayersAlive_OnePlayerIsDestroyed_resultIsFalse);
		 CPPUNIT_TEST(isPlayersAlive_OnePlayerNotDestroyedAskForPlayerNotInList_resultIsFalse);
		 CPPUNIT_TEST(constructor_twoHumanPlayersAndThreeComputerEnemies_playerCountIs5);
		 CPPUNIT_TEST(constructor_twoHumanPlayersAndThreeComputerEnemies_twoHumanPlayerIDs);
		 CPPUNIT_TEST(constructor_twoHumanPlayersAndThreeComputerEnemies_threeComputerEnemyIDs);
		 CPPUNIT_TEST(getAllNotDestroyedHumanPlayerIDs_oneOfTwoHumanPlayersDestroyed_resultSizeIs1);
		 CPPUNIT_TEST(getAllNotDestroyedComputerEnemyIDs_oneOfThreeComputerEnemiesDestroyed_resultSizeIs2);
		 CPPUNIT_TEST(isHumanPlayerID_humanPlayerID_true);
		 CPPUNIT_TEST(isHumanPlayerID_computerEnemyID_false);
		 CPPUNIT_TEST(getIndexOfHumanPlayer_humanPlayerID_smallerThanHumanPlayerCount);
		 CPPUNIT_TEST(getIndexOfComputerEnemy_computerEnemyID_smallerThanEnemyCount);
		 CPPUNIT_TEST(getWinnerOfGame_humanPlayerID_winnerTypePlayer1);
		 CPPUNIT_TEST(getWinnerOfGame_twoHumanPlayerID_winnerTypePlayer2);
		 CPPUNIT_TEST(getWinnerOfGame_humanPlayerIDAndComputerPlayerID_winnerTypeKI);
		 CPPUNIT_TEST(getWinnerOfGame_humanPlayerIDAndComputerPlayerID_winnerTypeDraw);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void addWall_defaultWall_wallCountIs1();
		 void addBomb_defaultBomb_bombCountIs1();
		 void getAllChangedWalls_twoWallsAdded_resultSizeIs2();
		 void getAllChangedWalls_oneWallAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1();
		 void getAllChangedBombs_twoBombsAdded_resultSizeIs2();
		 void getAllBombsLifeTime_afterReduceLifeTime_resultTimeIs2();
		 void getAllChangedBombs_twoBombsAddedAndOneDeleted_resultSizeIs1();
		 void getAllChangedBombs_oneBombAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1();
		 void getAllChangedExplodedBombs_oneExplodedBombAdded_resultSizeIs1();
		 void resetChangedFlags_oneWallAdded_wallIsNotChanged();
		 void resetChangedFlags_oneBombAdded_bombIsNotChanged();
		 void getHeight_heightLevelDefinition_resultIs50();
		 void getWidth_widthLevelDefinition_resultIs50();
		 void getAllBombsWithNegativeLifeTime_twoBombsAddedOneWithNegativeTime_resultSizeIs1();
		 void eraseWallById_twoWallsAddedOneDeleted_wallCountIs1();
		 void setBombsLifeTimeToZero_oneBombAddedAndSetLifeTimeZero_lifeTimeIs0();
		 void addPowerUp_defaultPowerUp_powerUpCountIs1();
		 void removePowerUpById_twoPowerUpsAdddedOneDeleted_PowerUpCountIs1();
		 void getAllChangedPowerUps_twoPowerUpsAdded_resultSizeIs2();
		 void getAllChangedPowerUps_onePowerUpAdedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1();
		 void resetChangedFlags_onePowerUpAdded_powerUpIsNotChanged();
		 void resetChangedFlags_oneExplodedBombAdded_noChangedExplodedBombs();
		 void getAllNotDestroyedPlayerIDs_onePlayerCreated_resultSizeIs1();
		 void constructor_3players_playerCountIs3();
		 void constructor_threePlayersOnDifferentPositions_allPlayersHaveDifferentPositions();
		 void setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_oneBombWithNoLifeTime_resultSizeIs1();
		 void setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_oneBombWithNoLifeTime_resultIsAddedBomb();
		 void setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_twoOfThreeBombsWithNoLifeTime_resultSizeIs2();
		 void setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs_oneBombWithNoLifeTime_explodedBombCountIs1();
		 void getExplodedBombByBomb_oneExplodedBombWithDestructionRange3_destructionRangeIs3();
		 void erasePlayerById_onePlayersAddedOneDeleted_playerCountIs0();
		 void getAllBombsWithDestroyedFlag_twoBombsAddedOneDestroyed_resultIs1();
		 void getAllWallsWithDestroyedFlag_twoWallsAddedOneDestroyed_resultIs1();
		 void getAllPowerUpsWithDestroyedFlag_twoPowerUpsAddedOneDestroyed_resultIs1();
		 void reduceAllBombsLifeTime_oneExplodedBomb_explodedBombsLifeTimeDecreased();
		 void removeAllObjectsWithDestroyedFlag_oneDestroyedExplodedBomb_explodedBombCountIs0();
		 void isPlayersAlive_OnePlayerNotDestroyed_resultIsTrue();
		 void isPlayersAlive_OnePlayerIsDestroyed_resultIsFalse();
		 void isPlayersAlive_OnePlayerNotDestroyedAskForPlayerNotInList_resultIsFalse();
		 void constructor_twoHumanPlayersAndThreeComputerEnemies_playerCountIs5();
		 void constructor_twoHumanPlayersAndThreeComputerEnemies_twoHumanPlayerIDs();
		 void constructor_twoHumanPlayersAndThreeComputerEnemies_threeComputerEnemyIDs();
		 void getAllNotDestroyedHumanPlayerIDs_oneOfTwoHumanPlayersDestroyed_resultSizeIs1();
		 void getAllNotDestroyedComputerEnemyIDs_oneOfThreeComputerEnemiesDestroyed_resultSizeIs2();
		 void isHumanPlayerID_humanPlayerID_true();
		 void isHumanPlayerID_computerEnemyID_false();
		 void getIndexOfHumanPlayer_humanPlayerID_smallerThanHumanPlayerCount();
		 void getIndexOfComputerEnemy_computerEnemyID_smallerThanEnemyCount();
		 void getWinnerOfGame_humanPlayerID_winnerTypePlayer1();
		 void getWinnerOfGame_twoHumanPlayerID_winnerTypePlayer2();
		 void getWinnerOfGame_humanPlayerIDAndComputerPlayerID_winnerTypeKI();
		 void getWinnerOfGame_humanPlayerIDAndComputerPlayerID_winnerTypeDraw();

	private:
		 UniqueIdCreator m_playerIDCreator;
		 UniqueIdCreator m_bombIDCreator;
		 UniqueIdCreator m_wallIDCreator;
		 UniqueIdCreator m_powerUpIDCreator;
	};
}

#endif
