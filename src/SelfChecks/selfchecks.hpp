// SPDX-License-Identifier: CC0-1.0
/**
 * @file selfchecks.hpp
 */
#ifndef NK_SELFCHECKS_HPP_
#define NK_SELFCHECKS_HPP_

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

	virtual void prepare() = 0;
	virtual void update()  = 0;
	virtual void verify()  = 0;
};

} // namespace work
} // namespace nk

#endif // NK_SELFCHECKS_HPP_
