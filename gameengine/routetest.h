#ifndef GAMEENGINE_ROUTETEST_H
#define GAMEENGINE_ROUTETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
	class RouteTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouteTest);
		CPPUNIT_TEST(constructor_distance5_distanceIs5);
		CPPUNIT_TEST(constructor_directionIsUp_directionIsUp);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_distance5_distanceIs5();
		void constructor_directionIsUp_directionIsUp();
	};
}

#endif
