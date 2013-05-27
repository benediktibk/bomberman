#ifndef COMMON_STOPWATCH_H
#define COMMON_STOPWATCH_H

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
	timeval m_start;
};
}

#endif
