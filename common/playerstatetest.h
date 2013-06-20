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
		CPPUNIT_TEST(constructor_validVParameter_destructionRangeIs1);
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
		CPPUNIT_TEST(countBomb_calledTwice_bombCountIs2);
		CPPUNIT_TEST(reduceBombCount_calledTwiceAndIncreasedThreeTimes_bombCountIs1);
		CPPUNIT_TEST(getRemainingBombs_maxBombCount5And2BombsPlaced_3);
		CPPUNIT_TEST(canPlaceBomb_maxBombCount2AndTwoBombsPlaced_false);
		CPPUNIT_TEST(canPlaceBomb_maxBombCount3AndTwoBombsPlaced_true);
		CPPUNIT_TEST(constructor_idCreator_maximumSpeedIs5);
		CPPUNIT_TEST(getSpeedIntoX_notMoving_0);
		CPPUNIT_TEST(getSpeedIntoY_notMoving_0);
		CPPUNIT_TEST(constructor_idCreator_isNotMoving);
		CPPUNIT_TEST(setMoving_empty_isMoving);
		CPPUNIT_TEST(setNotMoving_empty_isNotMoving);
		CPPUNIT_TEST(constructor_idCreator_widthIs1);
		CPPUNIT_TEST(constructor_idCreator_heightIs1);
		CPPUNIT_TEST(getCenterPosition_positionIs3And4_35And45);
		CPPUNIT_TEST(getSpeedIntoX_movingAndDirectionUp_0);
		CPPUNIT_TEST(getSpeedIntoX_movingAndDirectionDown_0);
		CPPUNIT_TEST(getSpeedIntoX_movingAndDirectionRight_maximumSpeed);
		CPPUNIT_TEST(getSpeedIntoX_movingAndDirectionLeft_minusMaximumSpeed);
		CPPUNIT_TEST(getSpeedIntoY_movingAndDirectionUp_maximumSpeed);
		CPPUNIT_TEST(getSpeedIntoY_movingAndDirectionDown_minusMaximumSpeed);
		CPPUNIT_TEST(getSpeedIntoY_movingAndDirectionLeft_0);
		CPPUNIT_TEST(getSpeedIntoY_movingAndDirectionRight_0);
		CPPUNIT_TEST(setHeight_5_heightIs5);
		CPPUNIT_TEST(setWidth_5_widthIs5);
		CPPUNIT_TEST(doNotCollideWith_validBomb_oneBombNotToCollideWith);
		CPPUNIT_TEST(doNotCollideWith_twoBombsRightBeside_twoBombsNotToCollideWith);
		CPPUNIT_TEST(removeBombFromDoNotCollideList_twoBombsAddedAndFirstOneExploded_oneBombNotToCollideWith);
		CPPUNIT_TEST(increaseSpeed_defaultSpeed_speedIncreasedByTwo);
		CPPUNIT_TEST(setDestructionRangeOfNewBombs_4_destructionRangeIs4);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void constructor_idCreator_idFetched();
		void constructor_validVParameter_destructionRangeIs1();
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
		void countBomb_calledTwice_bombCountIs2();
		void reduceBombCount_calledTwiceAndIncreasedThreeTimes_bombCountIs1();
		void getRemainingBombs_maxBombCount5And2BombsPlaced_3();
		void canPlaceBomb_maxBombCount2AndTwoBombsPlaced_false();
		void canPlaceBomb_maxBombCount3AndTwoBombsPlaced_true();
		void constructor_idCreator_maximumSpeedIs5();
		void getSpeedIntoX_notMoving_0();
		void getSpeedIntoY_notMoving_0();
		void constructor_idCreator_isNotMoving();
		void setMoving_empty_isMoving();
		void setNotMoving_empty_isNotMoving();
		void constructor_idCreator_widthIs1();
		void constructor_idCreator_heightIs1();
		void getCenterPosition_positionIs3And4_35And45();
		void getSpeedIntoX_movingAndDirectionUp_0();
		void getSpeedIntoX_movingAndDirectionDown_0();
		void getSpeedIntoX_movingAndDirectionRight_maximumSpeed();
		void getSpeedIntoX_movingAndDirectionLeft_minusMaximumSpeed();
		void getSpeedIntoY_movingAndDirectionUp_maximumSpeed();
		void getSpeedIntoY_movingAndDirectionDown_minusMaximumSpeed();
		void getSpeedIntoY_movingAndDirectionLeft_0();
		void getSpeedIntoY_movingAndDirectionRight_0();
		void setHeight_5_heightIs5();
		void setWidth_5_widthIs5();
		void doNotCollideWith_validBomb_oneBombNotToCollideWith();
		void doNotCollideWith_twoBombsRightBeside_twoBombsNotToCollideWith();
		void removeBombFromDoNotCollideList_twoBombsAddedAndFirstOneExploded_oneBombNotToCollideWith();
		void increaseSpeed_defaultSpeed_speedIncreasedByTwo();
		void setDestructionRangeOfNewBombs_4_destructionRangeIs4();

	private:
		UniqueIdCreator *m_playerIDCreator;
		UniqueIdCreator *m_bombIDCreator;
	};
}

#endif
