// SPDX-License-Identifier: CC0-1.0
/**
 * @file cyclictest.hpp
 */
#ifndef NK_CYCLICTEST_HPP_
#define NK_CYCLICTEST_HPP_

namespace nk {
namespace work {

class CyclicTest {
public:
	virtual ~CyclicTest();

	virtual void create_timerthread()   = 0;
	virtual void start_timerthread()    = 0;
	virtual void shutdown_timerthread() = 0;
};

} // namespace work
} // namespace nk

#endif // NK_CYCLICTEST_HPP_
