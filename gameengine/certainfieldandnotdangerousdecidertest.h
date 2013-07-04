#ifndef GAMEENGINE_CERTAINFIELDANDNOTDANGEROUSDECIDERTEST_H
#define GAMEENGINE_CERTAINFIELDANDNOTDANGEROUSDECIDERTEST_H

#include "common/gridpoint.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector>

namespace GameEngine
{
	class CertainFieldAndNotDangerousDeciderTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(CertainFieldAndNotDangerousDeciderTest);
		CPPUNIT_TEST(decide_notDangerousFieldWhichIsNotATarget_false);
		CPPUNIT_TEST(decide_dangerousFieldWhichIsATarget_false);
		CPPUNIT_TEST(decide_notDangerousFieldWhichIsATarget_true);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();

	private:
		void decide_notDangerousFieldWhichIsNotATarget_false();
		void decide_dangerousFieldWhichIsATarget_false();
		void decide_notDangerousFieldWhichIsATarget_true();

	private:
		std::vector<Common::GridPoint> m_targets;
	};
}

#endif
