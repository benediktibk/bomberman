#include "thread.h"
#include <signal.h>
#include <boost/thread.hpp>

using namespace Threading;

Thread::Thread() :
	m_thread(new boost::thread(threadFunction, this))
{ }

Thread::~Thread()
{
	m_thread->interrupt();
	waitTillFinished();
	delete m_thread;
}

void Thread::waitTillFinished() const
{
	m_thread->join();
}

void Thread::threadFunction(Thread *thread)
{
	thread->execute();
}