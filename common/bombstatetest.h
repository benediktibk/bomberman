#ifndef COMMON_BOMBSTATETEST_H
#define COMMON_BOMBSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class BombStateTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(BombStateTest);
	 CPPUNIT_TEST(setPosition_5And4_positionIs5And4);
	 CPPUNIT_TEST(setLifeTime_3_lifeTimeIs3);
	 CPPUNIT_TEST(setDestructionRange_5_DestructionRangeIs5);
	 CPPUNIT_TEST(setPosition_5And4_hasChanged);
	 CPPUNIT_TEST(setLifeTime_4_hasChanged);
	 CPPUNIT_TEST(setDestructionRange_5_hasChanged);
     CPPUNIT_TEST(getBombHeight_heightIs1);
     CPPUNIT_TEST(getBombWidth_widthIs1);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void setPosition_5And4_positionIs5And4();
	 void setLifeTime_3_lifeTimeIs3();
	 void setDestructionRange_5_DestructionRangeIs5();
	 void setPosition_5And4_hasChanged();
	 void setLifeTime_4_hasChanged();
	 void setDestructionRange_5_hasChanged();
     void getBombWidth_widthIs1();
     void getBombHeight_heightIs1();
};
}

#endif
