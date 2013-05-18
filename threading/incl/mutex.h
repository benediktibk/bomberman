#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

namespace Threading
{
class Mutex
{
public:
	Mutex();
	~Mutex();

	void lock();
	void free();

private:
	pthread_mutex_t m_mutex;
};
}

#endif
