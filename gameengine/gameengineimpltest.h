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
	CPPUNIT_TEST(updateGameState_tryToMoveThroughRightBorder_playerPositionIsAtRightBorder);
	CPPUNIT_TEST(updateGameState_tryToMoveThroughUpperBorder_playerPositionIsAtUpperBorder);
	CPPUNIT_TEST(updateGameState_tryToMoveThroughLowerBorder_playerPositionIsAtLowerBorder);
	CPPUNIT_TEST(updateGameState_tryToMoveThroughLeftBorder_playerPositionIsAtLeftBorder);
	CPPUNIT_TEST(updateGameState_Create4x4LevelWithSolidWallAndLetBombExplode_wallCountIs1);
	CPPUNIT_TEST(updateGameState_placeBombAndWaitTillItExploded_bombCountIs0);
	CPPUNIT_TEST(updateGameState_playerSurroundedByWallsAndTriesToMoveUp_playerMovedUp);
	CPPUNIT_TEST(updateGameState_playerSurroundedByWallsAndTriesToMoveRight_playerMovedRight);
	CPPUNIT_TEST(updateGameState_moveRightAndToUpperBorderAndBackAndTryToGetRightBetweenTwoWalls_playerMovedRight);
	CPPUNIT_TEST(updateGameState_halfTheTimeOfTheMovementToTheNextGridFieldButtonPressed_playerReachesGridPoint);
	CPPUNIT_TEST(updateGameState_playerVerticalBetweenTwoFieldsAndUpPressed_playerKeepsDirection);
	CPPUNIT_TEST(updateGameState_keyPressedHalfWayToGridFieldAndEnoughTimeToReachIt_playerPositionIsGridField);
	CPPUNIT_TEST(updateGameState_placeBombAndWaitExactTheBombLifeTime_bombCountIs0);
	CPPUNIT_TEST(getHeight_HeightOfLevelDefinition_HeightOfGamestate);
	CPPUNIT_TEST(getWidth_WidthOfLevelDefinition_WidthOfGamestate);
	CPPUNIT_TEST(getWallCount_Create4x4LevelWith2Wall_WallCount2);
	CPPUNIT_TEST(getWallPosition_Create4x4LevelWithWallPosition2And2_WallPosition2And2);
	CPPUNIT_TEST(getWallType_Create4x4LevelWallWithWallType_WallTypeIsLoose);
	CPPUNIT_TEST(getWallCount_Create4x4LevelWith2WallsOneWallInRangeOfBombAndBombExplodes_WallCount1);
	CPPUNIT_TEST(updateGameState_placeBombAtUpperBorder_bombCountIs0);
	CPPUNIT_TEST(getTimeTillPlayerReachesGridPoint_playerMovedHalfWayRightToGridPoint_halfTimeToMoveBetweenTwoGridPoints);
	CPPUNIT_TEST(getTimeTillPlayerReachesGridPoint_playerMovedHalfWayLeftToGridPoint_halfTimeToMoveBetweenTwoGridPoints);
	CPPUNIT_TEST(getTimeTillPlayerReachesGridPoint_playerMovedHalfWayUpToGridPoint_halfTimeToMoveBetweenTwoGridPoints);
	CPPUNIT_TEST(getTimeTillPlayerReachesGridPoint_playerMovedHalfWayDownToGridPoint_halfTimeToMoveBetweenTwoGridPoints);
	CPPUNIT_TEST(getTimeTillPlayerReachesGridPoint_playerStaysOnGridPoint_0);
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
	void updateGameState_halfTheTimeOfTheMovementToTheNextGridFieldButtonPressed_playerReachesGridPoint();
	void updateGameState_playerVerticalBetweenTwoFieldsAndUpPressed_playerKeepsDirection();
	void getWallCount_Create4x4LevelWith2WallsOneWallInRangeOfBombAndBombExplodes_WallCount1();
	void updateGameState_Create4x4LevelWithSolidWallAndLetBombExplode_wallCountIs1();
	void updateGameState_placeBombAndWaitTillItExploded_bombCountIs0();
	void updateGameState_placeBombAtUpperBorder_bombCountIs0();
	void updateGameState_playerSurroundedByWallsAndTriesToMoveUp_playerMovedUp();
	void updateGameState_playerSurroundedByWallsAndTriesToMoveRight_playerMovedRight();
	void updateGameState_moveRightAndToUpperBorderAndBackAndTryToGetRightBetweenTwoWalls_playerMovedRight();
	void getTimeTillPlayerReachesGridPoint_playerMovedHalfWayRightToGridPoint_halfTimeToMoveBetweenTwoGridPoints();
	void getTimeTillPlayerReachesGridPoint_playerMovedHalfWayLeftToGridPoint_halfTimeToMoveBetweenTwoGridPoints();
	void getTimeTillPlayerReachesGridPoint_playerMovedHalfWayUpToGridPoint_halfTimeToMoveBetweenTwoGridPoints();
	void getTimeTillPlayerReachesGridPoint_playerMovedHalfWayDownToGridPoint_halfTimeToMoveBetweenTwoGridPoints();
	void getTimeTillPlayerReachesGridPoint_playerStaysOnGridPoint_0();
	void updateGameState_keyPressedHalfWayToGridFieldAndEnoughTimeToReachIt_playerPositionIsGridField();
	void updateGameState_placeBombAndWaitExactTheBombLifeTime_bombCountIs0();
};
}

#endif
