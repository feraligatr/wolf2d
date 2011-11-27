#include "server_pch.h"

#include "server_pi.h"

using namespace boost::posix_time;
using namespace boost;

namespace pi
{

ptime startTime;

GSTATUS pi_init()
{
	startTime = microsec_clock::local_time();
	return GSTATUS_OK;
}

void pi_destroy()
{

}

time_ms_t getTickSinceStartup()
{
	return (microsec_clock::local_time() - startTime).total_milliseconds();
}

void thread_sleep(u32 interval)
{
	this_thread::sleep(boost::posix_time::milliseconds(interval));
}

}
