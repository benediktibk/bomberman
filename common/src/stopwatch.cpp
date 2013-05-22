#include "stopwatch.h"
#include <sys/time.h>

using namespace Common;

StopWatch::StopWatch()
{
	restart();
}

double StopWatch::getTimeAndRestart()
{
	double micro = 1000000;
	timeval end;
	gettimeofday(&end, 0);
	double result = (end.tv_sec - m_start.tv_sec)*micro + (end.tv_usec  - m_start.tv_usec);
	m_start = end;
	return result/micro;
}

void StopWatch::restart()
{
	gettimeofday(&m_start, 0);
}
