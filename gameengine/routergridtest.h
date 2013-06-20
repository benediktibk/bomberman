#ifndef GAMEENGINE_ROUTERGRIDTEST_H
#define GAMEENGINE_ROUTERGRIDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class UniqueIdCreator;
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

	private:
		Grid *m_grid;
		Common::UniqueIdCreator *m_bombIdCreator;
		Common::UniqueIdCreator *m_wallIdCreator;
		Common::UniqueIdCreator *m_powerUpIdCreator;
	};
}

#endif
