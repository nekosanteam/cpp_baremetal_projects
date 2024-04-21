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
 * @file cyclictest_main.cpp
 */

#include "cyclictest_main.h"

#include "cyclictest_itimer.hpp"
#include "cyclictest_nanosleep.hpp"

#include <memory>
#include <string>

namespace nk {
namespace work {

class impl {
public:
	impl();
};

} // namespace work
} // namespace nk

using std::make_unique;
using std::stoi;

namespace m = nk::work;

struct cyclictest_option {
	int duration;
};

struct cyclictest_option* cyclictest_parse_args(int argc, char** argv)
{
	auto opt = make_unique<struct cyclictest_option>();
	if (argc < 2) {
		opt->duration = 10;
	}
	else {
		opt->duration = stoi(argv[1], nullptr, 0);
	}
	return opt.release();
}

void cyclictest_free_option(struct cyclictest_option* opt)
{
	return;
}

int cyclictest_main(struct cyclictest_option* opt)
{
	//auto ptr = make_unique<m::CyclicTestITimer>();
	auto ptr = make_unique<m::CyclicTestNanoSleep>();

	ptr->create_timerthread();
	ptr->start_timerthread(opt->duration);
	ptr->shutdown_timerthread();

	return MAIN_SUCCESS;
}
