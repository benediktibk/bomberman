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
	 CPPUNIT_TEST_SUITE_END();

private:
	 void setPosition_5And4_positionIs5And4();
	 void setLifeTime_3_lifeTimeIs3();
	 void setDestructionRange_5_DestructionRangeIs5();
};
}

#endif
