#pragma once 

#include <cstddef>
#include <cstdint>
#include <array>

namespace work {

namespace MMIO {
using PhyAddr = std::uintptr_t;
using Offset  = unsigned int;

template<PhyAddr base, Offset offset, typename Access = std::uint32_t>
class Register {
public:
    static inline Access get() {
        return *(reinterpret_cast<volatile Access *>(base + offset));
    }

    static inline Access set(Access val) {
        *(reinterpret_cast<volatile Access*>(base + offset)) = val;
    }
};

template<PhyAddr base, Offset offset, unsigned int Num, typename Access = std::uint32_t>
class RegisterArray {
public:
    static inline Access get(int num) {
        return *(reinterpret_cast<volatile Access *>(base + offset + num * sizeof(Access)));
    }

    static inline Access set(int num, Access val) {
        *(reinterpret_cast<volatile Access*>(base + offset + num * sizeof(Access))) = val;
    }
};


} // namespace MMIO
} // namespace work
