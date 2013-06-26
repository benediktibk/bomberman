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
		CPPUNIT_TEST(constructor_positionIs5And4_positionIs5And4);
		CPPUNIT_TEST(setLifeTime_3_lifeTimeIs3);
		CPPUNIT_TEST(constructor_destructionRangeIs5_DestructionRangeIs5);
		CPPUNIT_TEST(setLifeTime_4_hasChanged);
		CPPUNIT_TEST(setDestroyed_empty_hasChanged);
		CPPUNIT_TEST(getBombWidth_widthIs1);
		CPPUNIT_TEST(getBombHeight_heightIs1);
		CPPUNIT_TEST(constructor_playerIDIs5_playerIDIs5);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_positionIs5And4_positionIs5And4();
		void setLifeTime_3_lifeTimeIs3();
		void constructor_destructionRangeIs5_DestructionRangeIs5();
		void setLifeTime_4_hasChanged();
		void setDestroyed_empty_hasChanged();
		void getBombWidth_widthIs1();
		void getBombHeight_heightIs1();
		void constructor_playerIDIs5_playerIDIs5();
	};
}

#endif
