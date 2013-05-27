#include "threading/thread.h"
#include <boost/thread.hpp>

using namespace Threading;

Thread::Thread() :
	m_thread(new boost::thread(threadFunction, this)),
	m_finished(false)
{ }

Thread::~Thread()
{
	if (!m_finished)
		m_thread->interrupt();
	waitTillFinished();
	delete m_thread;
}

void Thread::waitTillFinished() const
{
	if (!m_finished)
		m_thread->join();
}

void Thread::threadFunction(Thread *thread)
{
	thread->execute();
	thread->setFinished();
}

void Thread::setFinished()
{
	m_finished = true;
}
