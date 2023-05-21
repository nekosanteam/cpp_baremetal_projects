#pragma once
/* SPDX-License-Identifier: CC0-1.0 */
/**
 * @file mmio.hpp
 * 
 */
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>

namespace bm {
namespace work {

namespace MMIO {

namespace types {
using PhyAddr  = std::uintptr_t;
using VirAddr  = std::uintptr_t;
using LpaeAddr = std::uint64_t;

using Offset  = std::uintptr_t;
using PtrDiff = std::intptr_t;

using std::size_t;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
} // namespace types

template <types::PhyAddr ptr>
class PhyBase {
public:
	const static types::PhyAddr base_ { ptr };
	const static types::PhyAddr target_ { ptr };
};

template <types::PhyAddr ptr>
class VirBase {
public:
	types::VirAddr base_;
	const static types::PhyAddr target_ { ptr };

public:
	VirBase()
	    : base_(0)
	{
	}

	VirBase(const VirBase& base)
	    : base_(base.base_)
	{
	}

	VirBase& operator=(VirBase& rhs)
	{
		base_ = rhs.base_;
		return *this;
	}

	explicit VirBase(VirAddr base)
	    : base_(base)
	{
	}
	explicit VirBase(void* p)
	    : base_(reinterpret_cast<VirAddr>(p))
	{
	}
};

template <types::PhyAddr ptr>
class MMapBase {
public:
	std::uintptr_t base_;
	const static types::PhyAddr target_ { ptr };

private:
	int         fd_;
	std::size_t size_;

public:
	MMapBase()
	    : base_(0)
	    , fd_(-1)
	    , size_(0)
	{
	}
	MMapBase(const MMapBase& base) = delete;
	MMapBase(MMapBase&& rhs)
	    : base_(rhs.base_)
	    , fd_(rhs.fd_)
	    , size_(rhs.size_)
	{
	}
	MMapBase(PhyAddr base, std::size_t size);
	int  open();
	void close();
};

static inline types::uint8_t read8(const void* ptr, types::Offset off) noexcept
{
	return *(reinterpret_cast<const volatile types::uint8_t*>(ptr + off));
}

static inline types::uint16_t read16(const void* ptr, types::Offset off) noexcept
{
	assert((reinterpret_cast<uintptr_t>(ptr) & ~1u) == 0);
	assert((off & ~1u) == 0);
	return *(reinterpret_cast<const volatile types::uint16_t*>(ptr + off));
}

static inline types::uint32_t read32(const void* ptr, types::Offset off) noexcept
{
	assert((reinterpret_cast<uintptr_t>(ptr) & ~3u) == 0);
	assert((off & ~3u) == 0);
	return *(reinterpret_cast<const volatile types::uint32_t*>(ptr + off));
}

static inline types::uint64_t read64(const void* ptr, types::Offset off) noexcept
{
	assert((reinterpret_cast<uintptr_t>(ptr) & ~7u) == 0);
	assert((off & ~7u) == 0);
	return *(reinterpret_cast<const volatile types::uint64_t*>(ptr + off));
}

static inline void write8(void* ptr, types::Offset off, types::uint8_t v8) noexcept
{
	*(reinterpret_cast<volatile types::uint8_t*>(ptr + off)) = v8;
}

static inline void write16(void* ptr, types::Offset off, types::uint16_t v16) noexcept
{
	assert((reinterpret_cast<uintptr_t>(ptr) & ~1u) == 0);
	assert((off & ~1u) == 0);
	*(reinterpret_cast<volatile types::uint16_t*>(ptr + off)) = v16;
}

static inline void write32(void* ptr, types::Offset off, types::uint32_t v32) noexcept
{
	assert((reinterpret_cast<uintptr_t>(ptr) & ~3u) == 0);
	assert((off & ~3u) == 0);
	*(reinterpret_cast<volatile types::uint32_t*>(ptr + off)) = v32;
}

static inline void write64(void* ptr, types::Offset off, types::uint64_t v64) noexcept
{
	assert((reinterpret_cast<uintptr_t>(ptr) & ~7u) == 0);
	assert((off & ~7u) == 0);
	*(reinterpret_cast<volatile types::uint64_t*>(ptr + off)) = v64;
}

static inline types::uint16_t swapbytes2B(types::uint16_t v16) noexcept
{
	return (((v16 >> 8) & 0xFFu) | ((v16 & 0xFFu) << 16));
}

static inline types::uint32_t swapbytes4B(types::uint32_t v32) noexcept
{
	types::uint16_t v32_l = swapbytes2B(static_cast<types::uint16_t>((v32 >> 16) & 0xFFFFu));
	types::uint16_t v32_h = swapbytes2B(static_cast<types::uint16_t>(v32 & 0xFFFFu));
	return ((static_cast<types::uint32_t>(v32_h) << 16) | static_cast<types::uint32_t>(v32_l));
}

static inline types::uint64_t swapbytes8B(types::uint64_t v64) noexcept
{
	types::uint32_t v64_l = swapbytes4B(static_cast<types::uint32_t>((v64 >> 32) & 0xFFFFFFFFu));
	types::uint32_t v64_h = swapbytes4B(static_cast<types::uint32_t>(v64 & 0xFFFFFFFFu));

	return ((static_cast<types::uint64_t>(v64_h) << 32) | static_cast<types::uint64_t>(v64_l));
}

static inline types::uint8_t modify8(types::uint8_t v8, types::uint8_t m8, types::uint8_t s8) noexcept
{
	return ((v8 & ~m8) | s8);
}

static inline types::uint16_t modify16(types::uint16_t v16, types::uint16_t m16, types::uint16_t s16) noexcept
{
	return ((v16 & ~m16) | s16);
}

static inline types::uint32_t modify32(types::uint32_t v32, types::uint32_t m32, types::uint32_t s32) noexcept
{
	return ((v32 & ~m32) | s32);
}

static inline types::uint64_t modify64(types::uint64_t v64, types::uint64_t m64, types::uint64_t s64) noexcept
{
	return ((v64 & ~m64) | s64);
}

static inline types::uint8_t bitset8(types::uint8_t v8, int bit) noexcept
{
	assert((bit >= 0) && (bit < 8));
	return (v8 | (1u << bit));
}

static inline types::uint16_t bitset16(types::uint16_t v16, int bit) noexcept
{
	assert((bit >= 0) && (bit < 16));
	return (v16 | (1u << bit));
}

static inline types::uint32_t bitset32(types::uint32_t v32, int bit) noexcept
{
	assert((bit >= 0) && (bit < 32));
	return (v32 | (1u << bit));
}

static inline types::uint64_t bitset64(types::uint64_t v64, int bit) noexcept
{
	assert((bit >= 0) && (bit < 64));
	return (v64 | (1u << bit));
}

static inline types::uint8_t bitclr8(types::uint8_t v8, int bit) noexcept
{
	assert((bit >= 0) && (bit < 8));
	return modify8(v8, (1u << bit), 0);
}

static inline types::uint16_t bitclr16(types::uint16_t v16, int bit) noexcept
{
	assert((bit >= 0) && (bit < 16));
	return modify16(v16, (1u << bit), 0);
}

static inline types::uint32_t bitclr32(types::uint32_t v32, int bit) noexcept
{
	assert((bit >= 0) && (bit < 32));
	return modify32(v32, (1u << bit), 0);
}

static inline types::uint64_t bitclr64(types::uint64_t v64, int bit) noexcept
{
	assert((bit >= 0) && (bit < 64));
	return modify64(v64, (1u << bit), 0);
}

static inline types::uint8_t field8(types::uint8_t v8, types::uint8_t s8, int shift, int width) noexcept
{
	assert((shift >= 0) && (shift < 8));
	assert((width > 0) && (width <= 8));
	assert((shift + width) <= 8);

	if (width == 8) {
		return s8;
	}
	types::uint8_t m8 = ((1u << width) - 1);
	return modify8(v8, (m8 << shift), ((s8 & m8) << shift));
}

static inline types::uint16_t field16(types::uint16_t v16, types::uint16_t s16, int shift, int width) noexcept
{
	assert((shift >= 0) && (shift < 16));
	assert((width > 0) && (width <= 16));
	assert((shift + width) <= 16);

	if (width == 16) {
		return s16;
	}
	types::uint16_t m16 = ((1u << width) - 1);
	return modify16(v16, (m16 << shift), ((s16 & m16) << shift));
}

static inline types::uint32_t field32(types::uint32_t v32, types::uint32_t s32, int shift, int width) noexcept
{
	assert((shift >= 0) && (shift < 32));
	assert((width > 0) && (width <= 32));
	assert((shift + width) <= 32);

	if (width == 32) {
		return s32;
	}
	types::uint32_t m32 = ((1u << width) - 1);
	return modify32(v32, (m32 << shift), ((s32 & m32) << shift));
}

static inline types::uint64_t field64(types::uint64_t v64, types::uint64_t s64, int shift, int width) noexcept
{
	assert((shift >= 0) && (shift < 64));
	assert((width > 0) && (width <= 64));
	assert((shift + width) <= 64);

	if (width == 64) {
		return s64;
	}
	types::uint64_t m64 = ((1u << width) - 1);
	return modify64(v64, (m64 << shift), ((s64 & m64) << shift));
}

void* memcpy32(void* dst, const void* src, types::size_t size) noexcept;
void* memcpy64(void* dst, const void* src, types::size_t size) noexcept;
int   memcmp32(const void* r1, const void* r2, types::size_t size) noexcept;
int   memcmp64(const void* r1, const void* r2, types::size_t size) noexcept;

template <class BaseT>
class RegisterTableT : public BaseT {
public:
	using Base = BaseT;

	explicit RegisterTableT(Base base)
	    : Base(base)
	{
	}

public:
	inline types::uint8_t read8(types::Offset off) noexcept
	{
		return read8(reinterpret_cast<const volatile void*>(BaseT::base_), off);
	}

	inline types::uint16_t read16(types::Offset off) noexcept
	{
		return read16(reinterpret_cast<const volatile void*>(BaseT::base_), off);
	}

	inline types::uint32_t read32(types::Offset off) noexcept
	{
		return read32(reinterpret_cast<const volatile void*>(BaseT::base_), off);
	}

	inline types::uint64_t read64(types::Offset off) noexcept
	{
		return read64(reinterpret_cast<const volatile void*>(BaseT::base_), off);
	}

	inline void write8(types::Offset off, types::uint8_t v8) noexcept
	{
		write8(reinterpret_cast<volatile void*>(BaseT::base_), off, v8);
	}

	inline void write16(types::Offset off, types::uint16_t v16) noexcept
	{
		write16(reinterpret_cast<volatile void*>(BaseT::base_), off, v16);
	}

	inline void write32(types::Offset off, types::uint32_t v32) noexcept
	{
		write32(reinterpret_cast<volatile void*>(BaseT::base_), off, v32);
	}

	inline void write64(types::Offset off, types::int64_t v64) noexcept
	{
		write64(reinterpret_cast<volatile void*>(BaseT::base_), off, v64);
	}

	inline void modify8(Offset off, uint8_t field8, uint8_t v8) noexcept
	{
		uint8_t n8 = read8(off);
		n8         = ((n8 & ~field8) | v8);
		write8(off, n8);
	}

	inline void modify16(Offset off, uint16_t field16, uint16_t v16)
	{
		uint16_t n16 = read16(off);
		n16          = ((n16 & ~field16) | v16);
		write16(off, n16);
	}

	inline void modify32(Offset off, uint32_t field32, uint32_t v32)
	{
		uint32_t n32 = read32(off);
		n32          = ((n32 & ~field32) | v32);
		write32(off, n32);
	}

	inline void modify64(Offset off, uint64_t field64, uint64_t v64)
	{
		uint64_t n64 = read64(off);
		n64          = ((n64 & ~field64) | v64);
		write64(off, n64);
	}

	inline void clear8(Offset off, uint8_t field8)
	{
		modify8(off, field8, 0u);
	}

	inline void clear16(Offset off, uint16_t field16)
	{
		modify16(off, field16, 0u);
	}

	inline void clear32(Offset off, uint32_t field32)
	{
		modify32(off, field32, 0u);
	}

	inline void clear64(Offset off, uint64_t field64)
	{
		modify64(off, field64, 0u);
	}

	inline void set8(Offset off, int bit)
	{
		modify8(off, (1u << bit), (1u << bit));
	}

	inline void set16(Offset off, int bit)
	{
		modify16(off, (1u << bit), (1u << bit));
	}

	inline void set32(Offset off, int bit)
	{
		modify32(off, (1u << bit), (1u << bit));
	}

	inline void set64(Offset off, int bit)
	{
		modify64(off, (1u << bit), (1u << bit));
	}

	inline void reset8(Offset off, int bit)
	{
		modify8(off, (1u << bit), 0);
	}

	inline void reset16(Offset off, int bit)
	{
		modify16(off, (1u << bit), 0);
	}

	inline void reset32(Offset off, int bit)
	{
		modify32(off, (1u << bit), 0);
	}

	inline void reset64(Offset off, int bit)
	{
		modify64(off, (1u << bit), 0);
	}
};

template <class Base, Offset offset, typename Access = std::uint32_t>
class Register {
public:
	static inline Access get()
	{
		Access val = *(reinterpret_cast<volatile Access*>(Base::base_ + offset));
		return val;
	}

	static inline Access set(Access val)
	{
		*(reinterpret_cast<volatile Access*>(Base::base_ + offset)) = val;
		return val;
	}
};

template <class Base, Offset offset>
using Register64 = Register<Base, offset, std::uint64_t>;

template <class Base, Offset offset, unsigned int members, typename Access = std::uint32_t>
class RegisterArray {
public:
	static inline Access get(int num)
	{
		Access val = *(reinterpret_cast<volatile Access*>(Base::base_ + offset + num * sizeof(Access)));
		return val;
	}

	static inline Access set(int num, Access val)
	{
		*(reinterpret_cast<volatile Access*>(Base::base_ + offset + num * sizeof(Access))) = val;
		return val;
	}
};

template <class Base, Offset offset, unsigned int members>
using RegisterArray64 = RegisterArray<Base, offset, members, std::uint64_t>;

} // namespace MMIO
} // namespace work
} // namespace bm
