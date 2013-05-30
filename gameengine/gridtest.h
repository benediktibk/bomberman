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
     //CPPUNIT_TEST();
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
     //void
};
}

#endif



