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
 * @file selfchecks_main.cpp
 */

#include "selfchecks_main.h"

#include "selfchecks_mem.hpp"

#include <cstdint>
#include <memory>
#include <string>

using std::make_unique;
using std::stoull;
using std::uintptr_t;
using std::size_t;

namespace m = nk::work;

extern "C" {

struct selfchecks_option {
	uintptr_t target;
	size_t    size;
	int       pattern;
};

}

struct selfchecks_option* selfchecks_parse_args(int argc, char** argv)
{
	auto opt = make_unique<struct selfchecks_option>();
	if (argc < 2) {
		opt->target = 0;
	}
	else {
		opt->target = stoull(argv[1], nullptr, 0);
	}

	if (argc < 3) {
		opt->size = 4*1024;
	}
	else {
		opt->size = stoull(argv[2], nullptr, 0);
	}

	if (argc < 4) {
		opt->pattern = 0;
	}
	else {
		opt->pattern = stoull(argv[3], nullptr, 0);
	}

	return opt.release();
}

void selfchecks_free_option(struct selfchecks_option* opt)
{
	return;
}

int selfchecks_main(struct selfchecks_option* opt, pr_timespec time[])
{
	auto ptr = make_unique<m::SelfChecksMemory>();

	ptr->prepare(opt->target, opt->size, opt->pattern);
	time[0] = pr_getnowtime();
	ptr->update();
	time[1] = pr_getnowtime();
	ptr->verify();
	time[2] = pr_getnowtime();

	return MAIN_SUCCESS;
}
