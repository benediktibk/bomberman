#ifndef THREADING_MUTEX_H
#define THREADING_MUTEX_H

namespace boost
{
	class mutex;
}

namespace Threading
{
class Mutex
{
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();

private:
	boost::mutex *m_mutex;
};
}

#endif
