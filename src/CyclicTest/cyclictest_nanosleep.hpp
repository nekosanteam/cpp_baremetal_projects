// SPDX-License-Identifier: CC0-1.0
/**
 * @file cyclictest_nanosleep.hpp
 */
#ifndef NK_CYCLICTEST_NANOSLEEP_HPP_
#define NK_CYCLICTEST_NANOSLEEP_HPP_

#include "cyclictest.hpp"

#include <memory>

namespace nk {
namespace work {

class CyclicTestNanoSleep : public CyclicTest {
public:
	CyclicTestNanoSleep();
	virtual ~CyclicTestNanoSleep() override;

	virtual void create_timerthread() override;
	virtual void start_timerthread(int duration) override;
	virtual void shutdown_timerthread() override;

public:
	static void* timerthread(void* param);

public:
	class impl;
	std::shared_ptr<impl> m;
};

} // namespace work
} // namespace nk

#endif // NK_CYCLICTEST_NANOSLEEP_HPP_
