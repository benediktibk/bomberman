#include "thread.h"
#include <pthread.h>
#include <assert.h>

using namespace Threading;

Thread::Thread() :
	m_id(0)
{
	pthread_create(&m_id, 0, &threadFunction, this);
}

Thread::~Thread()
{
	pthread_cancel(m_id);
	m_id = 0;
}

void Thread::waitTillFinished() const
{
	void *exitStatus;
	pthread_join(m_id, &exitStatus);
}

void *Thread::threadFunction(void *threadAsVoid)
{
	Thread *thread = reinterpret_cast<Thread*>(threadAsVoid);
	assert(thread != 0);
	thread->execute();
	return 0;
}