#ifndef GAMEENGINE_ROUTERGRIDFIELDTEST_H
#define GAMEENGINE_ROUTERGRIDFIELDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
	class RouterGridFieldTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouterGridFieldTest);
		CPPUNIT_TEST(constructor_empty_isNotSolidWall);
		CPPUNIT_TEST(constructor_empty_isNotLooseWall);
		CPPUNIT_TEST(constructor_empty_isNotBomb);
		CPPUNIT_TEST(constructor_empty_isNotPlayer);
		CPPUNIT_TEST(constructor_empty_isNotDangerous);
		CPPUNIT_TEST(setSolidWall_true_isSolidWall);
		CPPUNIT_TEST(setLooseWall_true_isLooseWall);
		CPPUNIT_TEST(setBomb_true_isBomb);
		CPPUNIT_TEST(setBomb_true_isDangerous);
		CPPUNIT_TEST(setPlayer_true_isPlayer);
		CPPUNIT_TEST(setDangerous_true_isDangerous);
		CPPUNIT_TEST(isFree_nothingSet_true);
		CPPUNIT_TEST(isFree_bombSet_false);
		CPPUNIT_TEST(isFree_playerSet_false);
		CPPUNIT_TEST(isFree_looseWallSet_false);
		CPPUNIT_TEST(isFree_solidWallSet_false);
		CPPUNIT_TEST(isFree_dangerousSet_true);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_empty_isNotSolidWall();
		void constructor_empty_isNotLooseWall();
		void constructor_empty_isNotBomb();
		void constructor_empty_isNotPlayer();
		void constructor_empty_isNotDangerous();
		void setSolidWall_true_isSolidWall();
		void setLooseWall_true_isLooseWall();
		void setBomb_true_isBomb();
		void setBomb_true_isDangerous();
		void setPlayer_true_isPlayer();
		void setDangerous_true_isDangerous();
		void isFree_nothingSet_true();
		void isFree_bombSet_false();
		void isFree_playerSet_false();
		void isFree_looseWallSet_false();
		void isFree_solidWallSet_false();
		void isFree_dangerousSet_true();
	};
}

#endif
