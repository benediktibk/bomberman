#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <sys/types.h>

namespace Common
{
class StopWatch
{
public:
	StopWatch();

	double getTimeAndRestart();
	void restart();

private:
	clock_t m_start;
};
}

#endif
