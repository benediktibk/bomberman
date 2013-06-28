#ifndef THREADING_LOCK_H
#define THREADING_LOCK_H

namespace Threading
{
	class Mutex;

	class Lock
	{
	public:
		Lock(Mutex &mutex);
		~Lock();

	private:
		Mutex &m_mutex;
	};
}

#endif
