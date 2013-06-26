#ifndef THREADING_THREAD_H
#define THREADING_THREAD_H

namespace boost
{
	class thread;
}

namespace Threading
{
	class Signal;

	class Thread
	{
	public:
		Thread();
		virtual ~Thread();

		void waitTillFinished() const;

	protected:
		virtual void execute() = 0;
		void setConstructionFinished();

	private:
		static void threadFunction(Thread *thread);

	private:
		Threading::Signal *m_constructionFinished;
		Threading::Signal *m_finished;
		boost::thread *m_thread;
	};
}

#endif
