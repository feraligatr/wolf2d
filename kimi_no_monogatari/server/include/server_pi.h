#ifndef _SERVER_PI_H_
#define _SERVER_PI_H_

// TODO. classify the pi and move the pi into different files and directory

namespace pi
{

// do some initialization work for pi.
GSTATUS pi_init();
void pi_destroy();

typedef unsigned long long time_ms_t;
time_ms_t getTickSinceStartup();

void thread_sleep(u32 interval);

}
#endif /* _SERVER_PI_H_ */
