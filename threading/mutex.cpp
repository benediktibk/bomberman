#include "threading/mutex.h"
#include <boost/thread/mutex.hpp>

using namespace Threading;
using namespace boost;

Mutex::Mutex() :
	m_mutex(new mutex)
{ }

Mutex::~Mutex()
{
	delete m_mutex;
}

void Mutex::lock()
{
	m_mutex->lock();
}

void Mutex::unlock()
{
	m_mutex->unlock();
}
