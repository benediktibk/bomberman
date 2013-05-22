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

protected:
	virtual void execute() = 0;

private:
	static void threadFunction(Thread *thread);
	void setFinished();

private:
	boost::thread *m_thread;
	bool m_finished;
};
}

#endif
