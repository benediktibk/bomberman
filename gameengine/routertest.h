#ifndef GAMEENGINE_ROUTERTEST_H
#define GAMEENGINE_ROUTERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class LevelDefinition;
	class GameState;
	class UniqueIdCreator;
	class PlayerState;
	class Grid;
}

namespace GameEngine
{
	class Router;

	class RouterTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouterTest);
		CPPUNIT_TEST(constructor_validGrid_gridHasOneObserver);
		CPPUNIT_TEST(destructor_empty_gridHasNoObserver);
		CPPUNIT_TEST(getRouteToPlayer_secondPlayerTwoFieldsLeft_distanceIs2);
		CPPUNIT_TEST(getRouteToPlayer_secondPlayerTwoFieldsLeft_directionIsLeft);
		CPPUNIT_TEST(getRouteToPlayer_secondPlayerIsRightAndDirectWayBlocked_distanceIsWayAroundObstacle);
		CPPUNIT_TEST(getRouteToPlayer_secondPlayerIsRightButRightAndBelowIsWall_directionIsUp);
		CPPUNIT_TEST(getRouteToPlayer_noWayPossible_directionIsNone);
		CPPUNIT_TEST(getRouteToPlayer_noWayPossible_distanceIs0);
		CPPUNIT_TEST(getRouteToPlayer_bombInTheWay_distanceIsWayAroundBomb);
		CPPUNIT_TEST(getRouteToPlayer_wayBlockedByBomb_distanceIs0);
		CPPUNIT_TEST(getRouteToPlayer_wayBlockedByBomb_directionIsNone);
		CPPUNIT_TEST(getRouteToPlayer_jailedByWallsAtBorder_distanceIs0);
		CPPUNIT_TEST(getRouteToPlayer_jailedByWallsAtBorder_directionIsNone);
		CPPUNIT_TEST(getRouteToNotDangerousField_playerRightAtBomb_distanceIs2);
		CPPUNIT_TEST(getRouteToNotDangerousField_playerPositionNotDangerous_directionIsNone);
		CPPUNIT_TEST(getRouteToNotDangerousField_playerPositionNotDangerous_distanceIs0);
		CPPUNIT_TEST(getRouteToLooseWall_looseWallThreeFieldsAbovePlayer_distanceIs3);
		CPPUNIT_TEST(getRouteToLooseWall_looseWallThreeFieldsAbovePlayer_directionIsUp);
		CPPUNIT_TEST(getRouteToLooseWall_looseWallTwoFieldsLeftOfPlayer_distanceIs2);
		CPPUNIT_TEST(getRouteToLooseWall_looseWallTwoFieldsLeftOfPlayer_directionIsLeft);
		CPPUNIT_TEST(getRouteToLooseWall_looseWallTwoFieldsBelowOfPlayer_distanceIs2);
		CPPUNIT_TEST(getRouteToLooseWall_looseWallTwoFieldsBelowOfPlayer_directionIsDown);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void constructor_validGrid_gridHasOneObserver();
		void destructor_empty_gridHasNoObserver();
		void getRouteToPlayer_secondPlayerTwoFieldsLeft_distanceIs2();
		void getRouteToPlayer_secondPlayerTwoFieldsLeft_directionIsLeft();
		void getRouteToPlayer_secondPlayerIsRightAndDirectWayBlocked_distanceIsWayAroundObstacle();
		void getRouteToPlayer_secondPlayerIsRightButRightAndBelowIsWall_directionIsUp();
		void getRouteToPlayer_noWayPossible_directionIsNone();
		void getRouteToPlayer_noWayPossible_distanceIs0();
		void getRouteToPlayer_bombInTheWay_distanceIsWayAroundBomb();
		void getRouteToPlayer_wayBlockedByBomb_distanceIs0();
		void getRouteToPlayer_wayBlockedByBomb_directionIsNone();
		void getRouteToPlayer_jailedByWallsAtBorder_distanceIs0();
		void getRouteToPlayer_jailedByWallsAtBorder_directionIsNone();
		void getRouteToNotDangerousField_playerRightAtBomb_distanceIs2();
		void getRouteToNotDangerousField_playerPositionNotDangerous_directionIsNone();
		void getRouteToNotDangerousField_playerPositionNotDangerous_distanceIs0();
		void getRouteToLooseWall_looseWallThreeFieldsAbovePlayer_distanceIs3();
		void getRouteToLooseWall_looseWallThreeFieldsAbovePlayer_directionIsUp();
		void getRouteToLooseWall_looseWallTwoFieldsLeftOfPlayer_distanceIs2();
		void getRouteToLooseWall_looseWallTwoFieldsLeftOfPlayer_directionIsLeft();
		void getRouteToLooseWall_looseWallTwoFieldsBelowOfPlayer_distanceIs2();
		void getRouteToLooseWall_looseWallTwoFieldsBelowOfPlayer_directionIsDown();

	private:
		void createRouter(const Common::LevelDefinition &level);
		Common::PlayerState& getFirstPlayer();
		Common::PlayerState& getSecondPlayer();

	private:
		Common::Grid *m_grid;
		Common::UniqueIdCreator *m_playerIdCreator;
		Common::UniqueIdCreator *m_wallIdCreator;
		Common::UniqueIdCreator *m_bombIdCreator;
		Router *m_router;
		Common::GameState *m_gameState;
	};
}

#endif
