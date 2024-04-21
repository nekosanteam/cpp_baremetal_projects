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

#ifndef NK_SELFCHECKS_HPP_
#define NK_SELFCHECKS_HPP_
/**
 * @file selfchecks.hpp
 */

#include <cstdint>

namespace nk {
namespace work {

struct selfchecks_stats {
	double min;
	double max;
	double sum;
	int    count;
	int    shutdown;
	int    duration;
	int    processor;
};

class SelfChecks {
public:
	virtual ~SelfChecks();

	virtual void prepare(std::uintptr_t target, std::size_t size, int pattern) = 0;
	virtual void update() = 0;
	virtual void verify() = 0;
};

} // namespace work
} // namespace nk

#endif // NK_SELFCHECKS_HPP_
