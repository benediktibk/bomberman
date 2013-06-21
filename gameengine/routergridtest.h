#ifndef GAMEENGINE_ROUTERGRIDTEST_H
#define GAMEENGINE_ROUTERGRIDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class UniqueIdCreator;
	class GameState;
}

namespace GameEngine
{
	class Grid;

	class RouterGridTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouterGridTest);
		CPPUNIT_TEST(constructor_gridWith15RowsAnd10Columns_widthIs10);
		CPPUNIT_TEST(constructor_gridWith15RowsAnd10Columns_heightIs15);
		CPPUNIT_TEST(constructor_bombAt3And5InGrid_bombAt3And5);
		CPPUNIT_TEST(constructor_bombAt3And5InGrid_noSolidWallAt3And5);
		CPPUNIT_TEST(constructor_bombAt3And5InGrid_noLooseWallAt3And5);
		CPPUNIT_TEST(constructor_bombAt3And5InGrid_dangerousAt3And5);
		CPPUNIT_TEST(constructor_bombAt3And5InGrid_noPlayerAt3And5);
		CPPUNIT_TEST(constructor_looseWallAt7And5InGrid_looseWallAt7And5);
		CPPUNIT_TEST(constructor_looseWallAt7And5InGrid_noSolidWallAt7And5);
		CPPUNIT_TEST(constructor_looseWallAt7And5InGrid_noBombAt7And5);
		CPPUNIT_TEST(constructor_looseWallAt7And5InGrid_notDangerousAt7And5);
		CPPUNIT_TEST(constructor_looseWallAt7And5InGrid_noPlayerAt7And5);
		CPPUNIT_TEST(constructor_solidWallAt7And5InGrid_noLooseWallAt7And5);
		CPPUNIT_TEST(constructor_solidWallAt7And5InGrid_solidWallAt7And5);
		CPPUNIT_TEST(constructor_solidWallAt7And5InGrid_noBombAt7And5);
		CPPUNIT_TEST(constructor_solidWallAt7And5InGrid_notDangerousAt7And5);
		CPPUNIT_TEST(constructor_solidWallAt7And5InGrid_noPlayerAt7And5);
		CPPUNIT_TEST(constructor_powerUpAt8And9InGrid_noSolidWallAt8And9);
		CPPUNIT_TEST(constructor_powerUpAt8And9InGrid_noLooseWallAt8And9);
		CPPUNIT_TEST(constructor_powerUpAt8And9InGrid_noPlayerAt8And9);
		CPPUNIT_TEST(constructor_powerUpAt8And9InGrid_noBombAt8And9);
		CPPUNIT_TEST(constructor_powerUpAt8And9InGrid_notDangerousAt8And9);
		CPPUNIT_TEST(constructor_bombWithRange2At5And4_7And4IsDangerous);
		CPPUNIT_TEST(constructor_bombWithRange2At5And4_8And4IsNotDangerous);
		CPPUNIT_TEST(constructor_bombWithRange10At5And4AndWallAt6And4_7And4IsNotDangerous);
		CPPUNIT_TEST(constructor_bombWithRange2At5And4_3And4IsDangerous);
		CPPUNIT_TEST(constructor_bombWithRange2At5And4_2And4IsNotDangerous);
		CPPUNIT_TEST(constructor_bombWithRange10At5And4AndWallAt4And4_3And4IsNotDangerous);
		CPPUNIT_TEST(constructor_bombWithRange2At5And4_5And6IsDangerous);
		CPPUNIT_TEST(constructor_bombWithRange2At5And4_5And7IsNotDangerous);
		CPPUNIT_TEST(constructor_bombWithRange10At5And4AndWallAt5And5_5And6IsNotDangerous);
		CPPUNIT_TEST(constructor_bombWithRange2At5And4_5And2IsDangerous);
		CPPUNIT_TEST(constructor_bombWithRange2At5And4_5And1IsNotDangerous);
		CPPUNIT_TEST(constructor_bombWithRange10At5And4AndWallAt5And3_5And2IsNotDangerous);
		CPPUNIT_TEST(fieldHasChanged_bombAt4And3Removed_noBombAt4And3);
		CPPUNIT_TEST(fieldHasChanged_bombAt4And3Removed_5And3IsNotDangerous);
		CPPUNIT_TEST(fieldHasChanged_bombAt4And3RemovedAndBombAt7And4_7And3IsDangerous);
		CPPUNIT_TEST(fieldHasChanged_looseWallAt8And6Removed_noLooseWallAt8And6);
		CPPUNIT_TEST(fieldHasChanged_looseWallAt8And6RemovedAndBombWithRange10At7And6_9And6IsDangerous);
		CPPUNIT_TEST(updatePlayerFlags_playerMovementFrom4And5To4And6_noPlayerAt4And5);
		CPPUNIT_TEST(updatePlayerFlags_playerMovementFrom4And5To4And6_playerAt4And6);
		CPPUNIT_TEST(updatePlayerFlags_ownPlayerAt5And6_noPlayerAt5And6);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void constructor_gridWith15RowsAnd10Columns_widthIs10();
		void constructor_gridWith15RowsAnd10Columns_heightIs15();
		void constructor_bombAt3And5InGrid_bombAt3And5();
		void constructor_bombAt3And5InGrid_noSolidWallAt3And5();
		void constructor_bombAt3And5InGrid_noLooseWallAt3And5();
		void constructor_bombAt3And5InGrid_dangerousAt3And5();
		void constructor_bombAt3And5InGrid_noPlayerAt3And5();
		void constructor_looseWallAt7And5InGrid_looseWallAt7And5();
		void constructor_looseWallAt7And5InGrid_noSolidWallAt7And5();
		void constructor_looseWallAt7And5InGrid_noBombAt7And5();
		void constructor_looseWallAt7And5InGrid_notDangerousAt7And5();
		void constructor_looseWallAt7And5InGrid_noPlayerAt7And5();
		void constructor_solidWallAt7And5InGrid_noLooseWallAt7And5();
		void constructor_solidWallAt7And5InGrid_solidWallAt7And5();
		void constructor_solidWallAt7And5InGrid_noBombAt7And5();
		void constructor_solidWallAt7And5InGrid_notDangerousAt7And5();
		void constructor_solidWallAt7And5InGrid_noPlayerAt7And5();
		void constructor_powerUpAt8And9InGrid_noSolidWallAt8And9();
		void constructor_powerUpAt8And9InGrid_noLooseWallAt8And9();
		void constructor_powerUpAt8And9InGrid_noPlayerAt8And9();
		void constructor_powerUpAt8And9InGrid_noBombAt8And9();
		void constructor_powerUpAt8And9InGrid_notDangerousAt8And9();
		void constructor_bombWithRange2At5And4_7And4IsDangerous();
		void constructor_bombWithRange2At5And4_8And4IsNotDangerous();
		void constructor_bombWithRange10At5And4AndWallAt6And4_7And4IsNotDangerous();
		void constructor_bombWithRange2At5And4_3And4IsDangerous();
		void constructor_bombWithRange2At5And4_2And4IsNotDangerous();
		void constructor_bombWithRange10At5And4AndWallAt4And4_3And4IsNotDangerous();
		void constructor_bombWithRange2At5And4_5And6IsDangerous();
		void constructor_bombWithRange2At5And4_5And7IsNotDangerous();
		void constructor_bombWithRange10At5And4AndWallAt5And5_5And6IsNotDangerous();
		void constructor_bombWithRange2At5And4_5And2IsDangerous();
		void constructor_bombWithRange2At5And4_5And1IsNotDangerous();
		void constructor_bombWithRange10At5And4AndWallAt5And3_5And2IsNotDangerous();
		void fieldHasChanged_bombAt4And3Removed_noBombAt4And3();
		void fieldHasChanged_bombAt4And3Removed_5And3IsNotDangerous();
		void fieldHasChanged_bombAt4And3RemovedAndBombAt7And4_7And3IsDangerous();
		void fieldHasChanged_looseWallAt8And6Removed_noLooseWallAt8And6();
		void fieldHasChanged_looseWallAt8And6RemovedAndBombWithRange10At7And6_9And6IsDangerous();
		void updatePlayerFlags_playerMovementFrom4And5To4And6_noPlayerAt4And5();
		void updatePlayerFlags_playerMovementFrom4And5To4And6_playerAt4And6();
		void updatePlayerFlags_ownPlayerAt5And6_noPlayerAt5And6();

	private:
		unsigned int getFirstPlayerId() const;
		unsigned int getSecondPlayerId() const;

	private:
		Grid *m_grid;
		Common::GameState *m_gameState;
		Common::UniqueIdCreator *m_bombIdCreator;
		Common::UniqueIdCreator *m_wallIdCreator;
		Common::UniqueIdCreator *m_powerUpIdCreator;
		Common::UniqueIdCreator *m_playerIdCreator;
	};
}

#endif
