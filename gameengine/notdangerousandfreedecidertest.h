#ifndef GAMEENGINE_NOTDANGEROUSANDFREEDECIDERTEST_H
#define GAMEENGINE_NOTDANGEROUSANDFREEDECIDERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace GameEngine
{
	class NotDangerousAndFreeDeciderTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(NotDangerousAndFreeDeciderTest);
		CPPUNIT_TEST(decide_dangerousField_false);
		CPPUNIT_TEST(decide_wallAtField_false);
		CPPUNIT_TEST(decide_notDangerousAndFree_true);
		CPPUNIT_TEST_SUITE_END();

	private:
		void decide_dangerousField_false();
		void decide_wallAtField_false();
		void decide_notDangerousAndFree_true();
	};
}
#endif
