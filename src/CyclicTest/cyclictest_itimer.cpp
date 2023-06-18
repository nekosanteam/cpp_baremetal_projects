// SPDX-License-Identifier: CC0-1.0
/**
 * @file cyclictest_itimer.cpp
 */

#include "cyclictest_itimer.hpp"

#include "cyclictest.hpp"

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

namespace nk {
namespace work {

class CyclicTestITimer::impl {
public:

};

} // namespace work
} // namespace nk

namespace m = nk::work;

static inline void tsnorm(struct timespec* ts)
{
	ts->tv_sec += (ts->tv_nsec / (1000 * 1000 * 1000));
	ts->tv_nsec = (ts->tv_nsec % (1000 * 1000 * 1000));
}

static inline int64_t calcdiff(struct timespec t1, struct timespec t2)
{
	int64_t s1 = (static_cast<int64_t>(t1.tv_sec) * 1000 * 1000 * 100) + static_cast<int64_t>(t1.tv_nsec);
	int64_t s2 = (static_cast<int64_t>(t2.tv_sec) * 1000 * 1000 * 100) + static_cast<int64_t>(t2.tv_nsec);

	return (s1 - s2);
}

void* m::CyclicTestITimer::timerthread(void* param)
{
	sigset_t sigset;

	struct timespec now;
	struct timespec next;
	struct timespec interval;
	struct timespec stop;

	struct itimerval itimer;

	double diff;

	struct cyclictest_stats* st = reinterpret_cast<struct cyclictest_stats*>(param);

	::sigemptyset(&sigset);
	::sigaddset(&sigset, SIGALRM);
	::sigprocmask(SIG_BLOCK, &sigset, NULL);

	interval.tv_sec  = 0;
	interval.tv_nsec = 100000;

	clock_gettime(CLOCK_REALTIME, &now);
	stop = now;
	stop.tv_sec += st->duration;

	itimer.it_interval.tv_sec  = interval.tv_sec;
	itimer.it_interval.tv_usec = interval.tv_nsec / 1000;
	itimer.it_value = itimer.it_interval;
	setitimer(ITIMER_REAL, &itimer, NULL);

	//clock_gettime(CLOCK_REALTIME, &now);
	next = now;
	next.tv_sec  += interval.tv_sec;
	next.tv_nsec += interval.tv_nsec;
	tsnorm(&next);

	while (!st->shutdown) {
		int signo;
		if (sigwait(&sigset, &signo) < 0) {
			st->shutdown = 1;
			break;
		}
		clock_gettime(CLOCK_REALTIME, &now);
		diff = static_cast<double>(calcdiff(now, next));
		if (diff < st->min) {
			st->min = diff;
		}
		if (diff > st->max) {
			st->max = diff;
		}
		st->sum += diff;
		st->count++;

		if (calcdiff(now, stop) >= 0) {
			st->shutdown = 1;
		}

		do {
			next.tv_sec  += interval.tv_sec;
			next.tv_nsec += interval.tv_nsec;
			tsnorm(&next);
		} while (calcdiff(now, next) > 0);
	}

	itimer.it_interval.tv_sec  = 0;
	itimer.it_interval.tv_usec = 0;
	itimer.it_value.tv_sec     = 0;
	itimer.it_value.tv_usec    = 0;
	setitimer(ITIMER_REAL, &itimer, NULL);

	return NULL;
}

m::CyclicTest::~CyclicTest()
{
	return;
}

m::CyclicTestITimer::CyclicTestITimer()
{
	return;
}

m::CyclicTestITimer::~CyclicTestITimer()
{
	return;
}

void m::CyclicTestITimer::create_timerthread()
{
	return;
}

void m::CyclicTestITimer::start_timerthread()
{
	thread_t thr;

	pthread_create(&thr, NULL, thr, NULL);

	

	return;
}

void m::CyclicTestITimer::shutdown_timerthread()
{
	return;
}
