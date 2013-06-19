#ifndef GAMEENGINE_GRIDTEST_H
#define GAMEENGINE_GRIDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class UniqueIdCreator;
}

namespace GameEngine
{
	class GridTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(GridTest);
		CPPUNIT_TEST(isPlaceEmpty_TestOnEmptyVector_true);
		CPPUNIT_TEST(isPlaceEmpty_TestNotEmptyVector_false);
		CPPUNIT_TEST(addBombAtPlace_add_at3_3);
		CPPUNIT_TEST(getLooseWallsInRange_bombat32_twowallsup);
		CPPUNIT_TEST(getLooseWallsInRange_bombat32_twowallsright);
		CPPUNIT_TEST(getLooseWallsInRange_bombat32_twowallsleft);
		CPPUNIT_TEST(getLooseWallsInRange_bombat32_twowallsdown);
		CPPUNIT_TEST(getLooseWallsInRange_bombat32and4wallssurrounding_sizeofwallsinrangeis4);
		CPPUNIT_TEST(getLooseWallsInRange_bombat32and8wallssurroundingrangeis2_sizeofwallsinrangeis4);
		CPPUNIT_TEST(getLooseWallsInRange_bombat61rangeis2_sizeofwallsinrangeis3);
		CPPUNIT_TEST(getLooseWallsInRange_bombat32andwallssurroundingdistance2rangeis2_sizeofwallsinrangeis4);
		CPPUNIT_TEST(getLooseWallsInRange_bombat32andwallssurroundingdistance2rangeis1_sizeofwallsinrangeis0);
		CPPUNIT_TEST(getLooseWallsInRange_bombat60rangeis1_sizeofwallsinrangeis2);
		CPPUNIT_TEST(getPowerUpsInRange_bombat33rangeis4BombEmptyWallPowerUp_sizeofwallsinrangeis3);
		CPPUNIT_TEST(getPowerUpsInRange_bombat33RangeIs10PowerUpBombPowerUpPowerUpWallPowerUp_sizeOfPowerUpsInRangeIs3);
		CPPUNIT_TEST(getPowerUpsInRange_bombat59gridsize1010_expectassertionerroringetIndex);
		CPPUNIT_TEST(isPlaceEmpty_itemat33_false);
		CPPUNIT_TEST(isPlaceEmpty_itemat33_true);
		CPPUNIT_TEST(removeBomb_itemat33_true);
		CPPUNIT_TEST(removeWall_itemat33_true);
		CPPUNIT_TEST(removePowerUp_itemat33_true);
		CPPUNIT_TEST(getPlayerFields_PlayerAt1comm5and1_11and21);
		CPPUNIT_TEST(getPlayerFields_PlayerAt1and1comma5_11and12);
		CPPUNIT_TEST(addWallAtPlace_add_at3_3);
		CPPUNIT_TEST(removeBomb_from_3_3);
		CPPUNIT_TEST(removeWall_from_3_3);
		CPPUNIT_TEST(removeWall_addedWall_placeIsEmpty);
		CPPUNIT_TEST(isPlaceEmtpy_coveredByNothing_true);
		CPPUNIT_TEST(isPlaceEmpty_coveredByWall_false);
		CPPUNIT_TEST(getPlayersinRange_bombat59gridsize1010_1);
		CPPUNIT_TEST(getPlayersinRange_bombat59gridsize10x10_playersInRangeIs1);
		CPPUNIT_TEST(getPlayersinRange_bombat59gridsize10x10_playersInRangeIs0);
		CPPUNIT_TEST(getDistanceToNextWallLeft_nothingSet_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallRight_nothingSet_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallUp_nothingSet_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallDown_nothingSet_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallLeft_wallInRange_distanceIsWayToWall);
		CPPUNIT_TEST(getDistanceToNextWallRight_wallInRange_distanceIsWayToWall);
		CPPUNIT_TEST(getDistanceToNextWallUp_wallInRange_distanceIsWayToWall);
		CPPUNIT_TEST(getDistanceToNextWallDown_wallInRange_distanceIsWayToWall);
		CPPUNIT_TEST(getDistanceToNextWallLeft_powerUpInRange_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallRight_powerUpInRange_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallUp_powerUpInRange_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallDown_powerUpInRange_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallLeft_bombInRange_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallRight_bombInRange_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallUp_bombInRange_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST(getDistanceToNextWallDown_bombInRange_distanceIsWayToEndOfLevel);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void isPlaceEmpty_TestOnEmptyVector_true();
		void isPlaceEmpty_TestNotEmptyVector_false();
		void removeWall_from_3_3();
		void removeBomb_from_3_3();
		void addWallAtPlace_add_at3_3();
		void addBombAtPlace_add_at3_3();
		void getLooseWallsInRange_bombat32_twowallsup();
		void getLooseWallsInRange_bombat32_twowallsright();
		void getLooseWallsInRange_bombat32_twowallsleft();
		void getLooseWallsInRange_bombat32_twowallsdown();
		void getLooseWallsInRange_bombat32and4wallssurrounding_sizeofwallsinrangeis4();
		void getLooseWallsInRange_bombat32and8wallssurroundingrangeis2_sizeofwallsinrangeis4();
		void getLooseWallsInRange_bombat61rangeis2_sizeofwallsinrangeis3();
		void getLooseWallsInRange_bombat32andwallssurroundingdistance2rangeis2_sizeofwallsinrangeis4();
		void getLooseWallsInRange_bombat32andwallssurroundingdistance2rangeis1_sizeofwallsinrangeis0();
		void getLooseWallsInRange_bombat60rangeis1_sizeofwallsinrangeis2();
		void getPowerUpsInRange_bombat33rangeis4BombEmptyWallPowerUp_sizeofwallsinrangeis3();
		void getPowerUpsInRange_bombat33RangeIs10PowerUpBombPowerUpPowerUpWallPowerUp_sizeOfPowerUpsInRangeIs3();
		void getPowerUpsInRange_bombat59gridsize1010_expectassertionerroringetIndex();
		void isPlaceEmpty_itemat33_false();
		void isPlaceEmpty_itemat33_true();
		void removeBomb_itemat33_true();
		void removeWall_itemat33_true();
		void removePowerUp_itemat33_true();
		void getPlayerFields_PlayerAt1comm5and1_11and21();
		void getPlayerFields_PlayerAt1and1comma5_11and12();
		void removeWall_addedWall_placeIsEmpty();
		void isPlaceEmtpy_coveredByNothing_true();
		void isPlaceEmpty_coveredByWall_false();
		void getPlayersinRange_bombat59gridsize1010_1();
		void getPlayersinRange_bombat59gridsize10x10_playersInRangeIs1();
		void getPlayersinRange_bombat59gridsize10x10_playersInRangeIs0();
		void getDistanceToNextWallLeft_nothingSet_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallRight_nothingSet_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallUp_nothingSet_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallDown_nothingSet_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallLeft_wallInRange_distanceIsWayToWall();
		void getDistanceToNextWallRight_wallInRange_distanceIsWayToWall();
		void getDistanceToNextWallUp_wallInRange_distanceIsWayToWall();
		void getDistanceToNextWallDown_wallInRange_distanceIsWayToWall();
		void getDistanceToNextWallLeft_powerUpInRange_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallRight_powerUpInRange_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallUp_powerUpInRange_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallDown_powerUpInRange_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallLeft_bombInRange_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallRight_bombInRange_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallUp_bombInRange_distanceIsWayToEndOfLevel();
		void getDistanceToNextWallDown_bombInRange_distanceIsWayToEndOfLevel();

	private:
		Common::UniqueIdCreator *m_powerUpIdCreator;
		Common::UniqueIdCreator *m_wallIdCreator;
		Common::UniqueIdCreator *m_bombIdCreator;
	};
}

#endif



