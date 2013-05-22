#include "signaltest.h"
#include "signalcustom.h"
#include "threadcustom.h"

using namespace Threading;

class ThreadSignalTestImplementation :
		public Thread
{
public:
	ThreadSignalTestImplementation(Signal &signalValueSet, double &source, double &destination) :
		m_signalValueSet(signalValueSet),
		m_source(source),
		m_destination(destination)
	{ }

private:
	virtual void execute()
	{
		m_signalValueSet.wait();
		m_destination = m_source;
	}

private:
	Signal &m_signalValueSet;
	double &m_source;
	double &m_destination;
};

void SignalTest::send_threadWaitingOnSignalAndThenCopiesValue_destinationHasValueSetAfterCreationOfThread()
{
    CPPUNIT_ASSERT(false);
	double source = 0;
	double destination = 0;
	Signal signalValueSet;
	ThreadSignalTestImplementation thread(signalValueSet, source, destination);

	source = 5;
	signalValueSet.send();
	thread.waitTillFinished();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, destination, 0.00001);
}
