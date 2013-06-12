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
		CPPUNIT_TEST(constructor_bombWithDestructionRange3_destructionRangeIs3);
		CPPUNIT_TEST(setDestroyedIfNoLifeTimeLeft_lifeTimeGreaterZero_notDestroyed);
		CPPUNIT_TEST(setDestroyedIfNoLifeTimeLeft_lifeTimeSmallerZero_destroyed);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void constructor_validBombState_lifeTimeIsGreaterThanZero();
		void constructor_bombAtPosition4And5_positionIs4And5();
		void decreaseLifeTime_03_lifeTimeIs03Smaller();
		void constructor_bombWithDestructionRange3_destructionRangeIs3();
		void setDestroyedIfNoLifeTimeLeft_lifeTimeGreaterZero_notDestroyed();
		void setDestroyedIfNoLifeTimeLeft_lifeTimeSmallerZero_destroyed();

	private:
		UniqueIdCreator *m_bombIdCreator;
	};
}

#endif
