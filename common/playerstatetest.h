#ifndef COMMON_PLAYERSTATETEST_H
#define COMMON_PLAYERSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class UniqueIdCreator;

	class PlayerStateTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(PlayerStateTest);
		CPPUNIT_TEST(constructor_idCreator_idFetched);
		CPPUNIT_TEST(destructor_empty_idCountIsZero);
		CPPUNIT_TEST(setPosition_4And5_positionIs4And5);
		CPPUNIT_TEST(setDirectionUp_empty_directionIsUp);
		CPPUNIT_TEST(setDirectionDown_empty_directionIsDown);
		CPPUNIT_TEST(setDirectionRight_empty_directionIsRight);
		CPPUNIT_TEST(setDirectionLeft_empty_directionIsLeft);
		CPPUNIT_TEST(setMaxBombs_4_maxBombsIs4);
		CPPUNIT_TEST(constructor_idCreator_maxBombsIs1);
		CPPUNIT_TEST(increaseMaxBombs_calledTwice_maxBombsIs3);
		CPPUNIT_TEST(increaseMaxBombs_5_maxBombsIs6);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void constructor_idCreator_idFetched();
		void destructor_empty_idCountIsZero();
		void setPosition_4And5_positionIs4And5();
		void setDirectionUp_empty_directionIsUp();
		void setDirectionDown_empty_directionIsDown();
		void setDirectionRight_empty_directionIsRight();
		void setDirectionLeft_empty_directionIsLeft();
		void setMaxBombs_4_maxBombsIs4();
		void constructor_idCreator_maxBombsIs1();
		void increaseMaxBombs_calledTwice_maxBombsIs3();
		void increaseMaxBombs_5_maxBombsIs6();

	private:
		UniqueIdCreator *m_idCreator;
	};
}

#endif
