// SPDX-License-Identifier: CC0-1.0
/**
 * @file selfchecks_main.cpp
 */

#include "selfchecks_main.h"

#include "selfchecks_mem.hpp"

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

struct selfchecks_option {
	int duration;
};

struct selfchecks_option* selfchecks_parse_args(int argc, char** argv)
{
	auto opt = make_unique<struct selfchecks_option>();
	if (argc < 2) {
		opt->duration = 10;
	}
	else {
		opt->duration = stoi(argv[1], nullptr, 0);
	}
	return opt.release();
}

void selfchecks_free_option(struct selfchecks_option* opt)
{
	return;
}

int selfchecks_main(struct selfchecks_option* opt)
{
	auto ptr = make_unique<m::SelfChecksMemory>();

	ptr->prepare();
	ptr->update();
	ptr->verify();

	return MAIN_SUCCESS;
}
