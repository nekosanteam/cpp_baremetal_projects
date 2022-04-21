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
using Offset  = unsigned int;
using PhyAddr = std::uintptr_t;

template <PhyAddr ptr>
class PhyBase {
public:
	const static PhyAddr base_ { ptr };
};

using MmapAddr = std::uintptr_t;
template <int N>
class MmapBase {
public:
	static MmapAddr base_;

public:
    static int  open(PhyAddr base, std::size_t size);
    static void close();

private:
    int fd;
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
