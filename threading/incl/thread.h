#ifndef THREAD_H
#define THREAD_H

namespace boost
{
	class thread;
}

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

private:
	static void threadFunction(Thread *thread);

private:
	boost::thread *m_thread;
};
}

#endif
