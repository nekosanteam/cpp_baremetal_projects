// SPDX-License-Identifier: CC0-1.0
/**
 * @file cyclictest_main.cpp
 */

#include "cyclictest_main.h"

namespace m = nk::work;

namespace nk {
namespace work {

class impl {
public:
	impl();
};

} // namespace work
} // namespace nk

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
	return MAIN_SUCCESS;
}
