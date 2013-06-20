#ifndef GAMEENGINE_ROUTERGRIDTEST_H
#define GAMEENGINE_ROUTERGRIDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
	class Grid;

	class RouterGridTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouterGridTest);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:

	private:
		Grid *m_grid;
	};
}

#endif
