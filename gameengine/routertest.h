#ifndef GAMEENGINE_ROUTERTEST_H
#define GAMEENGINE_ROUTERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
	class LevelDefinition;
	class GameState;
	class UniqueIdCreator;
}

namespace GameEngine
{
	class Grid;
	class Router;

	class RouterTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouterTest);
		CPPUNIT_TEST(constructor_validGrid_gridHasOneObserver);
		CPPUNIT_TEST(destructor_empty_gridHasNoObserver);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void constructor_validGrid_gridHasOneObserver();
		void destructor_empty_gridHasNoObserver();

	private:
		void createRouter(const Common::LevelDefinition &level);

	private:
		Grid *m_grid;
		Common::UniqueIdCreator *m_playerIdCreator;
		Common::UniqueIdCreator *m_wallIdCreator;
		Router *m_router;
		Common::GameState *m_gameState;
	};
}

#endif
