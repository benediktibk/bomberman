#include "thread.h"
#include <assert.h>

using namespace Threading;

Thread::Thread() :
	m_id(0),
	m_running(true)
{
	int errorCode = pthread_create(&m_id, 0, &threadFunction, this);
	assert(errorCode == 0);
}

Thread::~Thread()
{
	if (m_running)
		pthread_cancel(m_id);
	waitTillFinished();
	m_id = 0;
	m_running = false;
}

void Thread::waitTillFinished() const
{
	void *exitStatus;
	if (m_running)
		pthread_join(m_id, &exitStatus);
}

void Thread::markAsFinished()
{
	m_running = false;
}

void *Thread::threadFunction(void *threadAsVoid)
{
	Thread *thread = reinterpret_cast<Thread*>(threadAsVoid);
	assert(thread != 0);
	thread->execute();
	thread->markAsFinished();
	return 0;
}