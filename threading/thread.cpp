#include "threading/thread.h"
#include "threading/signal.h"
#include <boost/thread.hpp>

using namespace Threading;

Thread::Thread() :
	m_finished(new Signal),
	m_thread(new boost::thread(threadFunction, this))
{ }

Thread::~Thread()
{
	waitTillFinished();
	delete m_finished;
	delete m_thread;
}

void Thread::waitTillFinished() const
{
	m_finished->wait();
}

void Thread::threadFunction(Thread *thread)
{
	thread->execute();
	thread->m_finished->send();
}
