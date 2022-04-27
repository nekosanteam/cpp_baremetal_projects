#pragma once
/**
 * @file  asm_a64.hpp
 * @brief
 *
 */
#include <cstddef>
#include <cstdint>

namespace bm {
namespace work {

static inline void sev()
{
	asm volatile("sev" : : : "memory");
}

static inline void sevl()
{
	asm volatile("sevl" : : : "memory");
}

static inline void wfe()
{
	asm volatile("wfe" : : : "memory");
}

static inline void wfi()
{
	asm volatile("wfi" : : : "memory");
}

static inline void nop()
{
	asm volatile("nop");
}

static inline void barrier()
{
	asm volatile("" : : : "memory");
}

#define dsb_(ty) asm volatile ("dsb" #ty : : : "memory")
#define dmb_(ty) asm volatile ("dmb" #ty : : : "memory")

static inline void isb() { asm volatile ("isb sy" : : : "memory"); }

static inline void dsb() { dsb_(sy); }

static inline void mb()  { dmb_(sy); }

static inline void rmb() { dmb_(ld); }

static inline void wmb() { dmb_(st); }

static inline void smp_mb()  { dmb_(ish); }

static inline void smp_rmb() { dmb_(ishld); }

static inline void smp_wmb() { dmb_(ishst); }

static inline std::uint64_t MPIDR_EL1() { asm volatile ("isb sy" : : : "memory"); }

static inline std::uint64_t CurrentEL() { std::uint64_t val; asm volatile ("mrs %0, CurrentEL" : : "r"(val)); return val; }


} // namespace work
} // namespace bm
