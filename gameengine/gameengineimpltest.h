#ifndef GAMEENGINE_GAMEENGINEIMPLTEST_H
#define GAMEENGINE_GAMEENGINEIMPLTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <map>
#include "common/inputstate.h"
#include "gameengine/gameengineimpl.h"

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
		CPPUNIT_TEST(updateGameState_moveTowardsWallAndAgainAway_playerPositionIsCorrect);
		CPPUNIT_TEST(updateGameState_pressRightAndThenUp_playerKeepsDirection);
		CPPUNIT_TEST(updateGameState_pressLeftAndThenDown_playerKeepsDirection);
		CPPUNIT_TEST(updateGameState_pressUpAndThenRight_playerKeepsDirection);
		CPPUNIT_TEST(updateGamestate_pressDownAndThenLeft_playerKeepsDirection);
		CPPUNIT_TEST(updateGameState_placeBombAndStayAtPlace_playerDoesntMove);
		CPPUNIT_TEST(updateGameState_placeBombMoveAwayAndTryToMoveThroughBomb_playerStaysBesideBomb);
		CPPUNIT_TEST(updateGameState_movementOfSecondPlayer_positionOfSecondPlayerIsCorrect);
		CPPUNIT_TEST(updateGameState_movementOfSecondPlayer_firstPlayerDoesntMove);
		CPPUNIT_TEST(updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsRight_explodedBombRangeRightIs1);
		CPPUNIT_TEST(updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsLeft_explodedBombRangeLeftIs1);
		CPPUNIT_TEST(updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsDown_explodedBombRangeDownIs1);
		CPPUNIT_TEST(updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsUp_explodedBombRangeUpIs1);
		CPPUNIT_TEST(updateGameState_playerWithDestructionRange5PlacesBomb_destructionRangeOfBombIs5);
		CPPUNIT_TEST(getHeight_HeightOfLevelDefinition_HeightOfGamestate);
		CPPUNIT_TEST(getWidth_WidthOfLevelDefinition_WidthOfGamestate);
		CPPUNIT_TEST(getWallCount_Create4x4LevelWith2Wall_WallCountIs2);
		CPPUNIT_TEST(getWallPosition_Create4x4LevelWithWallPosition2And2_WallPosition2And2);
		CPPUNIT_TEST(getWallType_Create4x4LevelWallWithWallType_WallTypeIsLoose);
		CPPUNIT_TEST(getWallCount_Create4x4LevelWith2WallsOneWallInRangeOfBombAndBombExplodes_WallCount1);
		CPPUNIT_TEST(updateGameState_placeBombAtUpperBorder_bombCountIs0);
		CPPUNIT_TEST(getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayRightToGridPoint_halfTimeToMoveBetweenTwoGridPoints);
		CPPUNIT_TEST(getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayLeftToGridPoint_halfTimeToMoveBetweenTwoGridPoints);
		CPPUNIT_TEST(getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayUpToGridPoint_halfTimeToMoveBetweenTwoGridPoints);
		CPPUNIT_TEST(getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayDownToGridPoint_halfTimeToMoveBetweenTwoGridPoints);
		CPPUNIT_TEST(getTimeTillOnePlayerReachesGridPoint_playerStaysOnGridPoint_veryLong);
		CPPUNIT_TEST(getTimeTillOnePlayerReachesGridPoint_playerIsMovingButDirectOnGridField_timeToReachNextGridField);
		CPPUNIT_TEST(increaseMaxBombCount_placeTwoBombsAtTheSameTime_BombCountIs2);
		CPPUNIT_TEST(increaseMaxBombCount_placeThreeBombsAtTheSameTime_BombCountIs2);
		CPPUNIT_TEST(setBombsLifeTimeToZero_placeTwoBombsOneExplodes_LifeTimeOfSecondBombIs0);
		CPPUNIT_TEST(getPlayerPosition_Create4x4LevelWithPlayerPosition2And2_PlayerPosition2And2);
		CPPUNIT_TEST(getPlayerCount_Create4x4LevelWith2Player_PlayerCountIs2);
		CPPUNIT_TEST(getPlayerCount_Create4x4LevelWith2PlayerOnePlayerDestroyed_PlayerCountIs1);
		CPPUNIT_TEST(addPowerUp_powerUpCountIs1PlayerWalksOnPowerUp_powerUpCountIs0);
		CPPUNIT_TEST(getPosition_getpositionaftercollisionwithotherplayer);
		CPPUNIT_TEST(updateGameState_AddTwoPowerUpsOneInRangeOfBombAndLetBombExplode_powerUpCountIs1);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

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
		void getWallCount_Create4x4LevelWith2Wall_WallCountIs2();
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
		void updateGameState_moveTowardsWallAndAgainAway_playerPositionIsCorrect();
		void updateGameState_pressRightAndThenUp_playerKeepsDirection();
		void updateGameState_pressLeftAndThenDown_playerKeepsDirection();
		void updateGameState_pressUpAndThenRight_playerKeepsDirection();
		void updateGamestate_pressDownAndThenLeft_playerKeepsDirection();
		void updateGameState_movementOfSecondPlayer_positionOfSecondPlayerIsCorrect();
		void updateGameState_movementOfSecondPlayer_firstPlayerDoesntMove();
		void updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsRight_explodedBombRangeRightIs1();
		void updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsLeft_explodedBombRangeLeftIs1();
		void updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsDown_explodedBombRangeDownIs1();
		void updateGameState_bombWithRange3ExplodesWithSolidWallTwoFieldsUp_explodedBombRangeUpIs1();
		void updateGameState_playerWithDestructionRange5PlacesBomb_destructionRangeOfBombIs5();
		void getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayRightToGridPoint_halfTimeToMoveBetweenTwoGridPoints();
		void getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayLeftToGridPoint_halfTimeToMoveBetweenTwoGridPoints();
		void getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayUpToGridPoint_halfTimeToMoveBetweenTwoGridPoints();
		void getTimeTillOnePlayerReachesGridPoint_playerMovedHalfWayDownToGridPoint_halfTimeToMoveBetweenTwoGridPoints();
		void getTimeTillOnePlayerReachesGridPoint_playerStaysOnGridPoint_veryLong();
		void getTimeTillOnePlayerReachesGridPoint_playerIsMovingButDirectOnGridField_timeToReachNextGridField();
		void updateGameState_keyPressedHalfWayToGridFieldAndEnoughTimeToReachIt_playerPositionIsGridField();
		void updateGameState_placeBombAndWaitExactTheBombLifeTime_bombCountIs0();
		void updateGameState_placeBombAndStayAtPlace_playerDoesntMove();
		void updateGameState_placeBombMoveAwayAndTryToMoveThroughBomb_playerStaysBesideBomb();
		void increaseMaxBombCount_placeTwoBombsAtTheSameTime_BombCountIs2();
		void increaseMaxBombCount_placeThreeBombsAtTheSameTime_BombCountIs2();
		void setBombsLifeTimeToZero_placeTwoBombsOneExplodes_LifeTimeOfSecondBombIs0();
		void getPlayerPosition_Create4x4LevelWithPlayerPosition2And2_PlayerPosition2And2();
		void getPlayerCount_Create4x4LevelWith2Player_PlayerCountIs2();
		void getPlayerCount_Create4x4LevelWith2PlayerOnePlayerDestroyed_PlayerCountIs1();
		void addPowerUp_powerUpCountIs1PlayerWalksOnPowerUp_powerUpCountIs0();
		void getPosition_getpositionaftercollisionwithotherplayer();
		void updateGameState_AddTwoPowerUpsOneInRangeOfBombAndLetBombExplode_powerUpCountIs1();

	private:
		void createGameEngine(const Common::LevelDefinition &level, unsigned int playerCount);
		void setFirstPlayerInput(const Common::InputState &input);
		void setSecondPlayerInput(const Common::InputState &input);

	private:
		std::map<unsigned int, Common::InputState> m_inputStates;
		GameEngineImpl *m_gameEngine;
		unsigned int m_firstPlayerID;
		unsigned int m_secondPlayerID;
	};
}

#endif
