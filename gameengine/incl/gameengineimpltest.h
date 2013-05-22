#ifndef GAMEENGINEIMPLTEST_H
#define GAMEENGINEIMPLTEST_H

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
     CPPUNIT_TEST_SUITE_END();

private:
     void updateGameState_UpKeyPressed_PlayerDirectionUp();
     void updateGameState_DownKeyPressed_PlayerDirectionDown();
     void updateGameState_LeftKeyPressed_PlayerDirectionLeft();
     void updateGameState_RightKeyPressed_PlayerDirectionRight();
};
}

#endif
