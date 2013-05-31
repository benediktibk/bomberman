#ifndef GAMEENGINE_GAMEENGINEIMPLTEST_H
#define GAMEENGINE_GAMEENGINEIMPLTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
class GameEngineImplTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(GameEngineImplTest);
	 CPPUNIT_TEST(updateGameState_UpKeyPressed_PlayerDirectionUp);
	 CPPUNIT_TEST(updateGameState_DownKeyPressed_PlayerDirectionDown);
	 CPPUNIT_TEST(updateGameState_LeftKeyPressed_PlayerDirectionLeft);
	 CPPUNIT_TEST(updateGameState_RightKeyPressed_PlayerDirectionRight);
	 CPPUNIT_TEST(updateGameState_oneBombPlaced_bombPositionIsSameAsPlayerPosition);
	 CPPUNIT_TEST(updateGameState_oneBombPlaced_bombLifeTimeIs2);
	 CPPUNIT_TEST(updateGameState_twoBombsPlacedAndOneDestroyed_bombCountIs1);
	 CPPUNIT_TEST(getHeight_HeightOfLevelDefinition_HeightOfGamestate);
	 CPPUNIT_TEST(getWidth_WidthOfLevelDefinition_WidthOfGamestate);
	 CPPUNIT_TEST(updateGameState_tryToMoveThroughRightBorder_playerPositionIsAtRightBorder);
	 CPPUNIT_TEST(updateGameState_tryToMoveThroughUpperBorder_playerPositionIsAtUpperBorder);
	 CPPUNIT_TEST(updateGameState_tryToMoveThroughLowerBorder_playerPositionIsAtLowerBorder);
	 CPPUNIT_TEST(updateGameState_tryToMoveThroughLeftBorder_playerPositionIsAtLeftBorder);
     CPPUNIT_TEST(getWallCount_Create4x4LevelWith2Wall_WallCount2);
     CPPUNIT_TEST(getWallPosition_Create4x4LevelWithWallPosition2And2_WallPosition2And2);
     CPPUNIT_TEST(getWallType_Create4x4LevelWallWithWallType_WallTypeIsLoose);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void updateGameState_UpKeyPressed_PlayerDirectionUp();
	 void updateGameState_DownKeyPressed_PlayerDirectionDown();
	 void updateGameState_LeftKeyPressed_PlayerDirectionLeft();
	 void updateGameState_RightKeyPressed_PlayerDirectionRight();
	 void updateGameState_oneBombPlaced_bombPositionIsSameAsPlayerPosition();
	 void updateGameState_oneBombPlaced_bombLifeTimeIs2();
	 void updateGameState_twoBombsPlacedAndOneDestroyed_bombCountIs1();
	 void getHeight_HeightOfLevelDefinition_HeightOfGamestate();
	 void getWidth_WidthOfLevelDefinition_WidthOfGamestate();
	 void updateGameState_tryToMoveThroughRightBorder_playerPositionIsAtRightBorder();
	 void updateGameState_tryToMoveThroughUpperBorder_playerPositionIsAtUpperBorder();
	 void updateGameState_tryToMoveThroughLowerBorder_playerPositionIsAtLowerBorder();
	 void updateGameState_tryToMoveThroughLeftBorder_playerPositionIsAtLeftBorder();
     void getWallCount_Create4x4LevelWith2Wall_WallCount2();
     void getWallPosition_Create4x4LevelWithWallPosition2And2_WallPosition2And2();
     void getWallType_Create4x4LevelWallWithWallType_WallTypeIsLoose();
};
}

#endif
