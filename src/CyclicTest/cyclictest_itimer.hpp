/* SPDX-License-Identifier: MIT-0 */
/**
 * @file cyclictest_itimer.hpp
 */
#ifndef NK_CYCLICTEST_ITIMER_HPP_
#define NK_CYCLICTEST_ITIMER_HPP_

#include "cyclictest.hpp"

#include <memory>

namespace nk {
namespace work {

class CyclicTestITimer : public CyclicTest {
public:
	CyclicTestITimer();
	virtual ~CyclicTestITimer() override;

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

#endif // NK_CYCLICTEST_ITIMER_HPP_
