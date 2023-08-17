/* SPDX-License-Identifier: MIT-0 */
/**
 * @file selfchecks.hpp
 */
#ifndef NK_SELFCHECKS_HPP_
#define NK_SELFCHECKS_HPP_

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
