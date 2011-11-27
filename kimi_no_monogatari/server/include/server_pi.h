#ifndef _SERVER_PI_H_
#define _SERVER_PI_H_

// TODO. classify the pi and move the pi into different files and directory

namespace pi
{

typedef int time_ms_t;
time_ms_t getCurrentTime();

void thread_sleep(u32 interval);

}
#endif /* _SERVER_PI_H_ */