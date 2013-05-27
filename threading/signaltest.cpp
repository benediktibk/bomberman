#include "signaltest.h"
#include "threading/signal.h"
#include "threading/threadcustom.h"
#include <unistd.h>

using namespace Threading;

class ThreadSignalTestImplementation :
		public Thread
{
public:
	ThreadSignalTestImplementation(Signal &signalValueSet, double &source, double &destination) :
		m_signalValueSet(signalValueSet),
		m_source(source),
		m_destination(destination),
		m_waitingStarted(false)
	{ }

	bool waitingStarted()
	{
		return m_waitingStarted;
	}

private:
	virtual void execute()
	{
		m_waitingStarted = true;
		m_signalValueSet.wait();
		m_destination = m_source;
	}

private:
	Signal &m_signalValueSet;
	double &m_source;
	double &m_destination;
	bool m_waitingStarted;
};

void SignalTest::send_threadWaitingOnSignalAndThenCopiesValue_destinationHasValueSetAfterCreationOfThread()
{
	double source = 0;
	double destination = 0;
	Signal signalValueSet;
	ThreadSignalTestImplementation thread(signalValueSet, source, destination);

	while (!thread.waitingStarted())
		usleep(1000);

	source = 5;
	signalValueSet.send();
	thread.waitTillFinished();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, destination, 0.00001);
}
