#ifndef GAMEENGINE_COVEREDBYLOOSEWALLDECIDERTEST_H
#define GAMEENGINE_COVEREDBYLOOSEWALLDECIDERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class Grid;
	class GameState;
	class LevelDefinition;
	class UniqueIdCreator;
}

namespace GameEngine
{
	class Router;

	class CoveredByLooseWallDeciderTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(CoveredByLooseWallDeciderTest);
		CPPUNIT_TEST(decide_defaultField_false);
		CPPUNIT_TEST(decide_looseWallAtField_true);
		CPPUNIT_TEST(decide_looseWallButCanNotEscape_false);
		CPPUNIT_TEST_SUITE_END();

	public:
		CoveredByLooseWallDeciderTest();
		virtual ~CoveredByLooseWallDeciderTest();

		virtual void setUp();
		virtual void tearDown();

	private:
		void decide_defaultField_false();
		void decide_looseWallAtField_true();
		void decide_looseWallButCanNotEscape_false();

	private:
		void createRouter(const Common::LevelDefinition &level);

	private:
		Common::UniqueIdCreator *m_playerIdCreator;
		Common::UniqueIdCreator *m_wallIdCreator;
		Common::UniqueIdCreator *m_bombIdCreator;
		Common::Grid *m_grid;
		Common::GameState *m_gameState;
		Router *m_router;
	};
}

#endif
