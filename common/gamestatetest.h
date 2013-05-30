#ifndef COMMON_GAMESTATETEST_H
#define COMMON_GAMESTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

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
	 CPPUNIT_TEST(getAllBombsLifeTime_AfterReduceLifeTime_resultTimeIs2);
	 CPPUNIT_TEST(getAllChangedBombs_twoBombsAddedAndOneDeleted_resultSizeIs1);
	 CPPUNIT_TEST(getAllChangedBombs_twoBombsAddedAndOneDeleted_bombCountIs1);
     CPPUNIT_TEST(getAllChangedBombs_oneBombAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1);
	 CPPUNIT_TEST(resetChangedFlags_oneWallAdded_wallIsNotChanged);
	 CPPUNIT_TEST(resetChangedFlags_oneBombAdded_bombIsNotChanged);
     CPPUNIT_TEST(getHeight_HeightLevelDefinition_resultIs50);
     CPPUNIT_TEST(getWidth_WidthLevelDefinition_resultIs50);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void addWall_defaultWall_wallCountIs1();
	 void addBomb_defaultBomb_bombCountIs1();
	 void getAllChangedWalls_twoWallsAdded_resultSizeIs2();
	 void getAllChangedWalls_oneWallAdedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1();
	 void getAllChangedBombs_twoBombsAdded_resultSizeIs2();
	 void getAllBombsLifeTime_AfterReduceLifeTime_resultTimeIs2();
	 void getAllChangedBombs_twoBombsAddedAndOneDeleted_resultSizeIs1();
	 void getAllChangedBombs_twoBombsAddedAndOneDeleted_bombCountIs1();
     void getAllChangedBombs_oneBombAddedAndChangedFlagsResetAndAnotherOneAdded_resultSizeIs1();
	 void resetChangedFlags_oneWallAdded_wallIsNotChanged();
	 void resetChangedFlags_oneBombAdded_bombIsNotChanged();
     void getHeight_HeightLevelDefinition_resultIs50();
     void getWidth_WidthLevelDefinition_resultIs50();
};
}

#endif
