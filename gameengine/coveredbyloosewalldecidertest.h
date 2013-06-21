#ifndef GAMEENGINE_COVEREDBYLOOSEWALLDECIDERTEST_H
#define GAMEENGINE_COVEREDBYLOOSEWALLDECIDERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
	class CoveredByLooseWallDeciderTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(CoveredByLooseWallDeciderTest);
		CPPUNIT_TEST(decide_defaultField_false);
		CPPUNIT_TEST(decide_looseWallAtField_true);
		CPPUNIT_TEST_SUITE_END();

	private:
		void decide_defaultField_false();
		void decide_looseWallAtField_true();
	};
}

#endif
