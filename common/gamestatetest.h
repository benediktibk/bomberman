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
	 CPPUNIT_TEST(eraseBomb_defaultBomb_bombCountIs1);
	 CPPUNIT_TEST(getAllChangedWalls_twoWallsAdded_resultSizeIs2);
	 CPPUNIT_TEST(getAllChangedBombs_twoBombsAdded_resultSizeIs2);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void addWall_defaultWall_wallCountIs1();
	 void addBomb_defaultBomb_bombCountIs1();
	 void eraseBomb_defaultBomb_bombCountIs1();
	 void getAllChangedWalls_twoWallsAdded_resultSizeIs2();
	 void getAllChangedBombs_twoBombsAdded_resultSizeIs2();
};
}

#endif
