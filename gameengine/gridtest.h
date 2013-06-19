#ifndef GAMEENGINE_GRIDTEST_H
#define GAMEENGINE_GRIDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
	class GridTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(GridTest);
		 CPPUNIT_TEST(isPlaceEmpty_TestOnEmptyVector_true);
		 CPPUNIT_TEST(isPlaceEmpty_TestNotEmptyVector_false);
		 CPPUNIT_TEST(addBombAtPlace_add_at3_3);
		 CPPUNIT_TEST(getWallsInRange_bombat32_twowallsup);
		 CPPUNIT_TEST(getWallsInRange_bombat32_twowallsright);
		 CPPUNIT_TEST(getWallsInRange_bombat32_twowallsleft);
		 CPPUNIT_TEST(getWallsInRange_bombat32_twowallsdown);
		 CPPUNIT_TEST(getWallsInRange_bombat32and4wallssurrounding_sizeofwallsinrangeis4);
		 CPPUNIT_TEST(getWallsInRange_bombat32and8wallssurroundingrangeis2_sizeofwallsinrangeis4);
		 CPPUNIT_TEST(getWallsInRange_bombat61rangeis2_sizeofwallsinrangeis3);
		 CPPUNIT_TEST(getWallsInRange_bombat32andwallssurroundingdistance2rangeis2_sizeofwallsinrangeis4);
		 CPPUNIT_TEST(getWallsInRange_bombat32andwallssurroundingdistance2rangeis1_sizeofwallsinrangeis0);
		 CPPUNIT_TEST(getWallsInRange_bombat60rangeis1_sizeofwallsinrangeis2);
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
		 CPPUNIT_TEST(getDistanceToNextNotFreePlaceLeft_nothingSet_distanceIsWayToEndOfLevel);
		 CPPUNIT_TEST(getDistanceToNextNotFreePlaceRight_nothingSet_distanceIsWayToEndOfLevel);
		 CPPUNIT_TEST(getDistanceToNextNotFreePlaceUp_nothingSet_distanceIsWayToEndOfLevel);
		 CPPUNIT_TEST(getDistanceToNextNotFreePlaceDown_nothingSet_distanceIsWayToEndOfLevel);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void isPlaceEmpty_TestOnEmptyVector_true();
		 void isPlaceEmpty_TestNotEmptyVector_false();
		 void removeWall_from_3_3();
		 void removeBomb_from_3_3();
		 void addWallAtPlace_add_at3_3();
		 void addBombAtPlace_add_at3_3();
		 void getWallsInRange_bombat32_twowallsup();
		 void getWallsInRange_bombat32_twowallsright();
		 void getWallsInRange_bombat32_twowallsleft();
		 void getWallsInRange_bombat32_twowallsdown();
		 void getWallsInRange_bombat32and4wallssurrounding_sizeofwallsinrangeis4();
		 void getWallsInRange_bombat32and8wallssurroundingrangeis2_sizeofwallsinrangeis4();
		 void getWallsInRange_bombat61rangeis2_sizeofwallsinrangeis3();
		 void getWallsInRange_bombat32andwallssurroundingdistance2rangeis2_sizeofwallsinrangeis4();
		 void getWallsInRange_bombat32andwallssurroundingdistance2rangeis1_sizeofwallsinrangeis0();
		 void getWallsInRange_bombat60rangeis1_sizeofwallsinrangeis2();
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
		 void getDistanceToNextNotFreePlaceLeft_nothingSet_distanceIsWayToEndOfLevel();
		 void getDistanceToNextNotFreePlaceRight_nothingSet_distanceIsWayToEndOfLevel();
		 void getDistanceToNextNotFreePlaceUp_nothingSet_distanceIsWayToEndOfLevel();
		 void getDistanceToNextNotFreePlaceDown_nothingSet_distanceIsWayToEndOfLevel();
	};
}

#endif



