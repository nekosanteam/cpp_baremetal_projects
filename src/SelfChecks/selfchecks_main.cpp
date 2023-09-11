/* SPDX-License-Identifier: MIT-0 */
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
