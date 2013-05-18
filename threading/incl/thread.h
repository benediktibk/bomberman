#ifndef THREAD_H
#define THREAD_H

namespace Threading
{
class Thread
{
public:
	Thread();
	~Thread();

	void waitTillFinished() const;

private:
	virtual void execute() = 0;

private:
	static void* threadFunction(void *threadAsVoid);

private:
	long unsigned int m_id;
};
}

#endif
