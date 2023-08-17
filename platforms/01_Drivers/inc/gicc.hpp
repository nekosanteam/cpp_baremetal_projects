/* SPDX-License-Identifier: MIT-0 */
#pragma once
/**
 * @file gicc.hpp
 * 
 */
#include <cstddef>
#include <cstdint>

namespace nk {
namespace work {

class GICD {
public:
	GICD() { }
	~GICD() { }

	void init();
    void init2nd();
	void enable(int intno);
	void disable(int intno);
};

class GICC {
public:
	GICC() { }
	~GICC() { }

	void init();
	void enable();
	void disable();
};

} // namespace work
} // namespace nk
