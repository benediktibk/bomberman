#ifndef GAMEENGINE_GRIDOBSERVERTEST_H
#define GAMEENGINE_GRIDOBSERVERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
	class Grid;

	class GridObserverTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(GridObserverTest);
		CPPUNIT_TEST(constructor_validGrid_gridHasObserverCount1);
		CPPUNIT_TEST(destructor_validGrid_gridHasObserverCount0);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void constructor_validGrid_gridHasObserverCount1();
		void destructor_validGrid_gridHasObserverCount0();

	private:
		Grid *m_grid;
	};
}

#endif
