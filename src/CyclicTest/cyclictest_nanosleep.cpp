/* SPDX-License-Identifier: MIT-0 */
/**
 * @file cyclictest_nanosleep.cpp
 */

#include "cyclictest_nanosleep.hpp"

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

#include <sched.h>

namespace nk {
namespace work {

class CyclicTestNanoSleep::impl {
public:

};

} // namespace work
} // namespace nk

namespace m = nk::work;

using pr_timespec = struct timespec;

static pr_timespec pr_gettime()
{
	pr_timespec now;

	clock_gettime(CLOCK_REALTIME, &now);

	return now;
}

static inline void pr_tsnorm(pr_timespec* ts)
{
	ts->tv_sec += (ts->tv_nsec / (1000 * 1000 * 1000));
	ts->tv_nsec = (ts->tv_nsec % (1000 * 1000 * 1000));
}

static inline int64_t calcdiff_ns(pr_timespec t1, pr_timespec t2)
{
	int64_t s1 = (static_cast<int64_t>(t1.tv_sec) * 1000 * 1000 * 1000) + static_cast<int64_t>(t1.tv_nsec);
	int64_t s2 = (static_cast<int64_t>(t2.tv_sec) * 1000 * 1000 * 1000) + static_cast<int64_t>(t2.tv_nsec);

	return (s1 - s2);
}

static inline pr_timespec calcadd_ns(pr_timespec t1, int64_t sec, int64_t nsec)
{
	pr_timespec ret;

	ret.tv_sec  = t1.tv_sec + sec;
	ret.tv_nsec = t1.tv_nsec + nsec;
	pr_tsnorm(&ret);

	return ret;
}

void* m::CyclicTestNanoSleep::timerthread(void* param)
{
	sigset_t  sigset;
	cpu_set_t cpuset;

	struct sched_param schedp {};

	pr_timespec now;
	pr_timespec next;
	pr_timespec interval;
	pr_timespec stop;

	struct timespec req;
	struct timespec rem;

	double diff;

	struct cyclictest_stats* st = reinterpret_cast<struct cyclictest_stats*>(param);

	CPU_ZERO(&cpuset);
	CPU_SET(st->processor, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) < 0) {
		perror("sched_setaffinity()");
	}

	schedp.sched_priority = 80;
	if(sched_setscheduler(0, SCHED_FIFO, &schedp) < 0) {
		perror("sched_setscheduler()");
	}

	interval.tv_sec  = 0;
	interval.tv_nsec = 100 * 1000;

	now  = pr_gettime();
	stop = calcadd_ns(now, 10, 0);

	now  = pr_gettime();
	next = calcadd_ns(now, interval.tv_sec, interval.tv_nsec);

	while (!st->shutdown) {
		req = calcadd_ns(now, interval.tv_sec, interval.tv_nsec);
		do {
			if (clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &req, nullptr) < 0) {
				if (errno == EINTR) {
					continue;
				} else {
					st->shutdown = 1;
				}
			}
		} while (0);
		if (st->shutdown) {
			break;
		}
		now = pr_gettime();
		diff = static_cast<double>(calcdiff_ns(now, next));
		if (diff >= 0.0) {
			if (diff < st->min) {
				st->min = diff;
			}
			if (diff > st->max) {
				st->max = diff;
			}
			st->sum += diff;
			st->count++;
		}

		if (calcdiff_ns(now, stop) >= 0) {
			st->shutdown = 1;
			break;
		}

		do {
			next = calcadd_ns(next, interval.tv_sec, interval.tv_nsec);
		} while (calcdiff_ns(now, next) > 0);
		now = next;
	}

	schedp.sched_priority = 0;
	sched_setscheduler(0, SCHED_OTHER, &schedp);

	return NULL;
}

m::CyclicTestNanoSleep::CyclicTestNanoSleep()
{
	return;
}

m::CyclicTestNanoSleep::~CyclicTestNanoSleep()
{
	return;
}

void m::CyclicTestNanoSleep::create_timerthread()
{
	return;
}

#define CYCLICTEST_PARALLEL (1)

void m::CyclicTestNanoSleep::start_timerthread(int duration)
{
	sigset_t  sigset;
	pthread_t thr[CYCLICTEST_PARALLEL];

	struct cyclictest_stats st[CYCLICTEST_PARALLEL];
	st[0].min   = 1000.0*1000.0*1000.0;
	st[0].max   = 0.0;
	st[0].sum   = 0.0;
	st[0].count = 0;
	st[0].shutdown  = 0;
	st[0].duration  = duration;
	st[0].processor = 1;

	::sigemptyset(&sigset);
	::sigaddset(&sigset, SIGALRM);
	::sigprocmask(SIG_BLOCK, &sigset, NULL);

	pthread_create(&thr[0], NULL, m::CyclicTestNanoSleep::timerthread, &st[0]);

	pthread_join(thr[0], NULL);

	for (int i=0; i<CYCLICTEST_PARALLEL; i++) {
		fprintf(stderr, "%.3f, %.3f, %.3f %d\n", st[i].min, st[i].max, (st[i].sum/(double)st[i].count), st[i].count);
	}

	return;
}

void m::CyclicTestNanoSleep::shutdown_timerthread()
{
	return;
}
