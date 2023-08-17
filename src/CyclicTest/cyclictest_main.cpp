/* SPDX-License-Identifier: MIT-0 */
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
