/* SPDX-License-Identifier: BSD-1-Clause */
/*
 * Copyright 2023,2024 nekosanteam <1688092+nekosanteam@users.noreply.github.com>. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS
 * AND CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @file selfchecks_mem.cpp
 */

#include "selfchecks_mem.hpp"

#include "selfchecks.hpp"

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

using std::uintptr_t;
using std::size_t;

namespace nk {
namespace work {

class SelfChecksMemory::impl {
public:
	uintptr_t target;
	size_t    size;
	int       pattern;
};

} // namespace work
} // namespace nk

namespace m = nk::work;

m::SelfChecks::~SelfChecks()
{
	return;
}

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

m::SelfChecksMemory::SelfChecksMemory()
{
	return;
}

m::SelfChecksMemory::~SelfChecksMemory()
{
	return;
}

void m::SelfChecksMemory::prepare(uintptr_t target, size_t size, int pattern)
{
	return;
}

void m::SelfChecksMemory::update()
{
	return;
}

void m::SelfChecksMemory::verify()
{
	return;
}
