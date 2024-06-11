/* SPDX-License-Identifier: BSD-1-Clause */
/*
 * Copyright 2024 nekosanteam <1688092+nekosanteam@users.noreply.github.com>. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS
 * AND CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once
/**
 * @file uintptrNN.hpp
 */
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>

namespace nk {
namespace work {

namespace ptr {

using uintptr12 = std::uint16_t;
using uintptr16 = std::uint16_t;
using uintptr24 = std::uint32_t;
using uintptr32 = std::uint32_t;
using uintptr48 = std::uint64_t;
using uintptr64 = std::uint64_t;

/* */
template <typename bitwidth, typename bitsign>
class OtC {
public:
	using uintptr_ = bitwidth;
	using intptr_  = bitsign;
	using size_    = bitwidth;
	using rsize_   = bitwidth;
	using ssize_   = bitsign;
	using ptrdiff_ = bitsign;
	using offset_  = bitsign;
};

template <class OffsetToStd>
class OtS {
public:
	using OffsetToStd16 = OtC<std::uint16_t, std::int16_t>

	static inline std::uint8_t  read8(void* base_,  OffsetToStd16::offset_ offs);
	static inline std::uint16_t read16(void* base_, OffsetToStd16::offset_ offs);
	static inline std::uint32_t read32(void* base_, OffsetToStd16::offset_ offs);
	static inline std::uint64_t read64(void* base_, OffsetToStd16::offset_ offs);

	static inline void write8(void* base_,  OffsetToStd16::offset_ offs, std::uint8_t val);
	static inline void write16(void* base_, OffsetToStd16::offset_ offs, std::uint16_t val);
	static inline void write32(void* base_, OffsetToStd16::offset_ offs, std::uint32_t val);
	static inline void write64(void* base_, OffsetToStd16::offset_ offs, std::uint64_t val);
};

class Base {
public:
	Base(void* p) : base_(reinterpret_cast<std::uintptr_t>(p)) {}

	inline std::uintptr_t base() { return base_; }
	inline std::intptr_t  offset() { return 0; }
	inline std::uintptr_t size() { return RSIZE_MAX; }

public:
	std::uintptr_t base_;
};


}

}
}
