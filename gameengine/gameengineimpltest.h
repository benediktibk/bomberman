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
};
}

#endif
