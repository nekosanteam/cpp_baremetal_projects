// SPDX-License-Identifier: CC0-1.0
/**
 * @file cyclictest_itimer.hpp
 */
#ifndef NK_CYCLICTEST_ITIMER_HPP_
#define NK_CYCLICTEST_ITIMER_HPP_

#include "cyclictest.hpp"

namespace nk {
namespace work {

class CyclicTestITimer : public CyclicTest {
public:
	CyclicTestITimer();
	virtual ~CyclicTestITimer() override;

	virtual void create_timerthread() override;
	virtual void start_timerthread() override;
	virtual void shutdown_timerthread() override;
};

} // namespace work
} // namespace nk

#endif // NK_CYCLICTEST_ITIMER_HPP_
