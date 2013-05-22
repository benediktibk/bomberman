#ifndef STOPWATCHTEST_H
#define STOPWATCHTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Common
{
class StopWatchTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(StopWatchTest);
	 CPPUNIT_TEST(getTimeAndRestart_waitOf10msSinceLastCall_001);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void getTimeAndRestart_waitOf10msSinceLastCall_001();
};
}

#endif
