#ifndef COMMON_EXPLODEDBOMBSTATETEST_H
#define COMMON_EXPLODEDBOMBSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class UniqueIdCreator;

	class ExplodedBombStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(ExplodedBombStateTest);
		CPPUNIT_TEST(constructor_validBombState_lifeTimeIsGreaterThanZero);
		CPPUNIT_TEST(constructor_bombAtPosition4And5_positionIs4And5);
		CPPUNIT_TEST(decreaseLifeTime_03_lifeTimeIs03Smaller);
		CPPUNIT_TEST(decreaseLifeTime_4_hasChanged);
		CPPUNIT_TEST(constructor_bombWithDestructionRange3_maximumDestructionRangeIs3);
		CPPUNIT_TEST(setDestroyedIfNoLifeTimeLeft_lifeTimeGreaterZero_notDestroyed);
		CPPUNIT_TEST(setDestroyedIfNoLifeTimeLeft_lifeTimeSmallerZero_destroyed);
		CPPUNIT_TEST(constructor_bombWithCertainHeight_heightIsTheSame);
		CPPUNIT_TEST(constructor_bombWithCertainWidth_widthIsTheSame);
		CPPUNIT_TEST(constructor_maximumDestructionRange3_destructionRangeLeftIs3);
		CPPUNIT_TEST(constructor_maximumDestructionRange3_destructionRangeUpIs3);
		CPPUNIT_TEST(constructor_maximumDestructionRange3_destructionRangeRightIs3);
		CPPUNIT_TEST(constructor_maximumDestructionRange3_destructionRangeDownIs3);
		CPPUNIT_TEST(setDestructionRangeLeft_2_destructionRangeLeftIs2);
		CPPUNIT_TEST(setDestructionRangeUp_2_destructionRangeUpIs2);
		CPPUNIT_TEST(setDestructionRangeRight_2_destructionRangeRightIs2);
		CPPUNIT_TEST(setDestructionRangeDown_2_destructionRangeDownIs2);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void constructor_validBombState_lifeTimeIsGreaterThanZero();
		void constructor_bombAtPosition4And5_positionIs4And5();
		void decreaseLifeTime_03_lifeTimeIs03Smaller();
		void decreaseLifeTime_4_hasChanged();
		void constructor_bombWithDestructionRange3_maximumDestructionRangeIs3();
		void setDestroyedIfNoLifeTimeLeft_lifeTimeGreaterZero_notDestroyed();
		void setDestroyedIfNoLifeTimeLeft_lifeTimeSmallerZero_destroyed();
		void constructor_bombWithCertainHeight_heightIsTheSame();
		void constructor_bombWithCertainWidth_widthIsTheSame();
		void constructor_maximumDestructionRange3_destructionRangeLeftIs3();
		void constructor_maximumDestructionRange3_destructionRangeUpIs3();
		void constructor_maximumDestructionRange3_destructionRangeRightIs3();
		void constructor_maximumDestructionRange3_destructionRangeDownIs3();
		void setDestructionRangeLeft_2_destructionRangeLeftIs2();
		void setDestructionRangeUp_2_destructionRangeUpIs2();
		void setDestructionRangeRight_2_destructionRangeRightIs2();
		void setDestructionRangeDown_2_destructionRangeDownIs2();

	private:
		UniqueIdCreator *m_bombIdCreator;
	};
}

#endif
