#ifndef SIGNAL_H
#define SIGNAL_H

namespace boost
{
	class condition_variable;
	class mutex;
}

namespace Threading
{
class Signal
{
public:
	Signal();
	~Signal();

	void send();
	void reset();
	void wait();

private:
	boost::condition_variable *m_condition;
	boost::mutex *m_conditionMutex;
	boost::mutex *m_sendingMutex;
	bool m_sent;
};
}

#endif
