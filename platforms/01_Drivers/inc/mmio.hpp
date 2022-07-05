#pragma once
/**
 * @file mmio.hpp
 * 
 */
#include <array>
#include <cstddef>
#include <cstdint>

namespace bm {
namespace work {

namespace MMIO {
namespace types {
using Offset   = std::uintptr_t;
using PhyAddr  = std::uintptr_t;
using VirAddr  = std::uintptr_t;
using LpaeAddr = std::uint64_t;

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
} // MMIO::types

using namespace types;

template <PhyAddr ptr>
class PhyBase {
public:
	const static PhyAddr base_ { ptr };
};

class VirBase {
public:
    VirAddr base_;

public:
    VirBase() : base_(0) {}
    VirBase(const VirBase& base) : base_(base.base_) {}
    VirBase& operator=(VirBase& rhs) {
        base_ = rhs.base_;
        return *this;
    }

    explicit VirBase(VirAddr base) : base_(base) {}
    explicit VirBase(void* p) : base_(reinterpret_cast<VirAddr>(p)) {}
};

class MMapBase {
public:
	std::uintptr_t base_;

private:
    int fd_;
    std::size_t size_;

public:
    MMapBase() : base_(0), fd_(-1), size_(0) {}
    MMapBase(const MMapBase& base) = delete;
    MMapBase(MMapBase&& rhs) : base_(rhs.base_), fd_(rhs.fd_), size_(rhs.size_) {}
    MMapBase(PhyAddr base, std::size_t size);
    int open();
    void close();
};

template <class BaseT>
class RegisterTableT : public BaseT {
public:
    using Base = BaseT;

    explicit RegisterTableT(Base base) : Base(base) {}

public:
    inline uint8_t  read8(Offset off)
    {
        return *(reinterpret_cast<volatile uint8_t*>(BaseT::base_ + off));
    }

    inline uint16_t read16(Offset off)
    {
        return *(reinterpret_cast<volatile uint16_t*>(BaseT::base_ + off));
    }

    inline uint32_t read32(Offset off)
    {
        return *(reinterpret_cast<volatile uint32_t*>(BaseT::base_ + off));
    }

    inline uint64_t read64(Offset off)
    {
        return *(reinterpret_cast<volatile uint64_t*>(BaseT::base_ + off));
    }

    inline void write8(Offset off, uint8_t v8)
    {
        *(reinterpret_cast<volatile uint8_t*>(BaseT::base_ + off)) = v8;
    }

    inline void write16(Offset off, uint16_t v16)
    {
        *(reinterpret_cast<volatile uint16_t*>(BaseT::base_ + off)) = v16;
    }

    inline void write32(Offset off, uint32_t v32)
    {
        *(reinterpret_cast<volatile uint32_t*>(BaseT::base_ + off)) = v32;
    }

    inline void write64(Offset off, uint64_t v64)
    {
        *(reinterpret_cast<volatile uint64_t*>(BaseT::base_ + off)) = v64;
    }

    inline void modify8(Offset off, uint8_t mask8, uint8_t v8)
    {
        uint8_t n8 = read8(off);
        n8 = ((n8 & mask8) | v8);
        write8(off, n8);
    }

    inline void modify16(Offset off, uint16_t mask16, uint16_t v16)
    {
        uint16_t n16 = read16(off);
        n16 = ((n16 & mask16) | v16);
        write16(off, n16);
    }

    inline void modify32(Offset off, uint32_t mask32, uint32_t v32)
    {
        uint32_t n32 = read32(off);
        n32 = ((n32 & mask32) | v32);
        write32(off, n32);
    }

    inline void modify64(Offset off, uint64_t mask64, uint64_t v64)
    {
        uint64_t n64 = read64(off);
        n64 = ((n64 & mask64) | v64);
        write64(off, n64);
    }

    inline void clear8(Offset off, uint8_t bits8)
    {
        modify8(off, ~bits8, 0u);
    }

    inline void clear16(Offset off, uint16_t bits16)
    {
        modify16(off, ~bits16, 0u);
    }

    inline void clear32(Offset off, uint32_t bits32)
    {
        modify32(off, ~bits32, 0u);
    }

    inline void clear64(Offset off, uint64_t bits64)
    {
        modify64(off, ~bits64, 0u);
    }

    inline void set8(Offset off, int bit)
    {
        modify8(off, ~(1u<<bit), (1u<<bit));
    }

    inline void set16(Offset off, int bit)
    {
        modify16(off, ~(1u<<bit), (1u<<bit));
    }

    inline void set32(Offset off, int bit)
    {
        modify32(off, ~(1u<<bit), (1u<<bit));
    }

    inline void set64(Offset off, int bit)
    {
        modify64(off, ~(1u<<bit), (1u<<bit));
    }

    inline void reset8(Offset off, int bit)
    {
        modify8(off, ~(1u<<bit), 0);
    }

    inline void reset16(Offset off, int bit)
    {
        modify16(off, ~(1u<<bit), 0);
    }

    inline void reset32(Offset off, int bit)
    {
        modify32(off, ~(1u<<bit), 0);
    }

    inline void reset64(Offset off, int bit)
    {
        modify64(off, ~(1u<<bit), 0);
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
