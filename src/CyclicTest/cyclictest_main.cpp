// SPDX-License-Identifier: CC0-1.0
/**
 * @file cyclictest_main.cpp
 */

#include "cyclictest_main.h"

#include "cyclictest_itimer.hpp"

#include <memory>

namespace nk {
namespace work {

class impl {
public:
	impl();
};

} // namespace work
} // namespace nk

using std::make_unique;

namespace m = nk::work;

struct cyclictest_option {
	void* ptr;
};

struct cyclictest_option* cyclictest_parse_args(int argc, char** argv)
{
	return nullptr;
}

void cyclictest_free_option(struct cyclictest_option* opt)
{
	return;
}

int cyclictest_main(struct cyclictest_option* opt)
{
	auto ptr = make_unique<m::CyclicTestITimer>();

	ptr->create_timerthread();
	ptr->start_timerthread();
	ptr->shutdown_timerthread();

	return MAIN_SUCCESS;
}
