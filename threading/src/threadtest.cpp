#include "threadtest.h"
#include "thread.h"

using namespace Threading;

class ThreadImpl :
		public Thread
{
public:
	ThreadImpl() :
		m_value(0)
	{ }

	int getValue() const
	{
		return m_value;
	}

private:
	virtual void execute()
	{
		m_value = 5;
	}

private:
	int m_value;
};

void ThreadTest::constructor_setValueTo5DuringExecution_valueIs5()
{
	ThreadImpl thread;

	thread.waitTillFinished();

	CPPUNIT_ASSERT_EQUAL((int)5, thread.getValue());
}