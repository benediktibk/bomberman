#ifndef SIGNALTEST_H
#define SIGNALTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Threading
{
class SignalTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(SignalTest);
	 CPPUNIT_TEST(send_threadWaitingOnSignalAndThenCopiesValue_destinationHasValueSetAfterCreationOfThread);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void send_threadWaitingOnSignalAndThenCopiesValue_destinationHasValueSetAfterCreationOfThread();
};
}

#endif
