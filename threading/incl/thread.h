#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

namespace Threading
{
class Thread
{
public:
	Thread();
	virtual ~Thread();

	void waitTillFinished() const;

private:
	virtual void execute() = 0;
	void markAsFinished();

private:
	static void* threadFunction(void *threadAsVoid);

private:
	pthread_t m_id;
	bool m_running;
};
}

#endif
