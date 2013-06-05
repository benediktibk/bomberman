#ifndef COMMON_STOPWATCH_H
#define COMMON_STOPWATCH_H

#include <boost/timer.hpp>

namespace Common
{
class StopWatch
{
public:
	StopWatch();

	double getTimeAndRestart();
	void restart();

private:
    boost::timer m_start;
};
}

#endif
