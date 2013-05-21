#include "stopwatch.h"
#include <time.h>

using namespace Common;

StopWatch::StopWatch() :
	m_start(clock())
{ }

double StopWatch::getTimeAndRestart()
{
	clock_t end = clock();
	double result = (end - m_start)/CLOCKS_PER_SEC;
	restart();
	return result;
}

void StopWatch::restart()
{
	m_start = clock();
}
