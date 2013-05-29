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
     CPPUNIT_TEST(updateGameState_SpaceKeyPressed_BombPlaced_testPosition);
     CPPUNIT_TEST(updateGameState_SpaceKeyPressed_BombPlaced_testBombLifeTime_resultIs2);
     CPPUNIT_TEST(updateGameState_SpaceKeyPressed_towBombsPlaced_oneBombDelete_testBombCount_resultIs1);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void updateGameState_UpKeyPressed_PlayerDirectionUp();
	 void updateGameState_DownKeyPressed_PlayerDirectionDown();
	 void updateGameState_LeftKeyPressed_PlayerDirectionLeft();
	 void updateGameState_RightKeyPressed_PlayerDirectionRight();
     void updateGameState_SpaceKeyPressed_BombPlaced_testPosition();
     void updateGameState_SpaceKeyPressed_BombPlaced_testBombLifeTime_resultIs2();
     void updateGameState_SpaceKeyPressed_towBombsPlaced_oneBombDelete_testBombCount_resultIs1();
};
}

#endif
