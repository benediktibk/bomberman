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
	 CPPUNIT_TEST(setPosition_5And4_positionIs5And4);
	 CPPUNIT_TEST(construct_solidWall_typeIsSolidWall);
	 CPPUNIT_TEST(construct_looseWall_typeIsLooseWall);
	 CPPUNIT_TEST(setPosition_5And4_hasChanged);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void setPosition_5And4_positionIs5And4();
	 void construct_solidWall_typeIsSolidWall();
	 void construct_looseWall_typeIsLooseWall();
	 void setPosition_5And4_hasChanged();
};
}

#endif
