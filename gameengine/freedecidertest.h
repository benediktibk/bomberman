#ifndef GAMEENGINE_FREEDECIDERTEST_H
#define GAMEENGINE_FREEDECIDERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
	class FreeDeciderTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FreeDeciderTest);
		CPPUNIT_TEST(decide_defaultField_true);
		CPPUNIT_TEST(decide_solidWallAtField_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void decide_defaultField_true();
		void decide_solidWallAtField_false();
	};
}

#endif
