// SPDX-License-Identifier: CC0-1.0
/**
 * @file selfchecks_mem.hpp
 */
#ifndef NK_SELFCHECKS_MEM_HPP_
#define NK_SELFCHECKS_MEM_HPP_

#include "selfchecks.hpp"

#include <memory>

namespace nk {
namespace work {

class SelfChecksMemory : public SelfChecks {
public:
	SelfChecksMemory();
	virtual ~SelfChecksMemory() override;

	virtual void prepare(std::uintptr_t target, std::size_t size, int pattern) override;
	virtual void update() override;
	virtual void verify() override;

public:
	class impl;
	std::shared_ptr<impl> m;
};

} // namespace work
} // namespace nk

#endif // NK_SELFCHECKS_MEM_HPP_
