#include "stopwatch.h"
#include <sys/time.h>


using namespace Common;

StopWatch::StopWatch()
{
	restart();
}

double StopWatch::getTimeAndRestart()
{
    double t=m_start.elapsed();
    restart();
    return t;
}

void StopWatch::restart()
{
    m_start.restart();
}
