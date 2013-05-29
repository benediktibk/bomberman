#ifndef COMMON_WALLSTATETEST_H
#define COMMON_WALLSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class WallStateTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(WallStateTest);
	 CPPUNIT_TEST(construct_solidWall_typeIsSolidWall);
	 CPPUNIT_TEST(construct_looseWall_typeIsLooseWall);
     CPPUNIT_TEST(getWallHeight_heightIs1);
     CPPUNIT_TEST(getWallWidth_widthIs1);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void construct_solidWall_typeIsSolidWall();
	 void construct_looseWall_typeIsLooseWall();
     void getWallWidth_widthIs1();
     void getWallHeight_heightIs1();
};
}

#endif
