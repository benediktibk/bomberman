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
		 CPPUNIT_TEST(getAllChangedWalls_oneWallAdedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1);
		 CPPUNIT_TEST(getAllChangedBombs_twoBombsAdded_resultSizeIs2);
		 CPPUNIT_TEST(getAllBombsLifeTime_afterReduceLifeTime_resultTimeIs2);
		 CPPUNIT_TEST(getAllChangedBombs_twoBombsAddedAndOneDeleted_resultSizeIs1);
		 CPPUNIT_TEST(getAllChangedBombs_oneBombAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1);
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
		 CPPUNIT_TEST(getAllPossiblePlayerIDs_onePlayerCreated_resultSizeIs1);
		 CPPUNIT_TEST(constructor_3players_playerCountIs3);
		 CPPUNIT_TEST(constructor_threePlayersOnDifferentPositions_allPlayersHaveDifferentPositions);
		 CPPUNIT_TEST(setAllBombsWithNoLifeTimeDestroyed_oneBombWithNoLifeTime_resultSizeIs1);
		 CPPUNIT_TEST(setAllBombsWithNoLifeTimeDestroyed_oneBombWithNoLifeTime_resultIsAddedBomb);
		 CPPUNIT_TEST(setAllBombsWithNoLifeTimeDestroyed_twoOfThreeBombsWithNoLifeTime_resultSizeIs2);
		 CPPUNIT_TEST(erasePlayerById_onePlayersAddedOneDeleted_playerCountIs0);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void addWall_defaultWall_wallCountIs1();
		 void addBomb_defaultBomb_bombCountIs1();
		 void getAllChangedWalls_twoWallsAdded_resultSizeIs2();
		 void getAllChangedWalls_oneWallAdedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1();
		 void getAllChangedBombs_twoBombsAdded_resultSizeIs2();
		 void getAllBombsLifeTime_afterReduceLifeTime_resultTimeIs2();
		 void getAllChangedBombs_twoBombsAddedAndOneDeleted_resultSizeIs1();
		 void getAllChangedBombs_oneBombAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1();
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
		 void getAllPossiblePlayerIDs_onePlayerCreated_resultSizeIs1();
		 void constructor_3players_playerCountIs3();
		 void constructor_threePlayersOnDifferentPositions_allPlayersHaveDifferentPositions();
		 void setAllBombsWithNoLifeTimeDestroyed_oneBombWithNoLifeTime_resultSizeIs1();
		 void setAllBombsWithNoLifeTimeDestroyed_oneBombWithNoLifeTime_resultIsAddedBomb();
		 void setAllBombsWithNoLifeTimeDestroyed_twoOfThreeBombsWithNoLifeTime_resultSizeIs2();
		 void erasePlayerById_onePlayersAddedOneDeleted_playerCountIs0();

	private:
		 UniqueIdCreator m_playerIDCreator;
		 UniqueIdCreator m_bombIDCreator;
		 UniqueIdCreator m_wallIDCreator;
		 UniqueIdCreator m_powerUpIDCreator;
	};
}

#endif
