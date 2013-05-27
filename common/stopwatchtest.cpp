#include "stopwatchtest.h"
#include "stopwatch.h"
#include "time.h"
#include <unistd.h>

using namespace Common;

void StopWatchTest::getTimeAndRestart_waitOf10msSinceLastCall_001()
{
	StopWatch watch;

	watch.getTimeAndRestart();
	usleep(10000);
	double time = watch.getTimeAndRestart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.01, time, 0.001);
}
