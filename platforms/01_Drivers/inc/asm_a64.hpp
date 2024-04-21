/* SPDX-License-Identifier: BSD-1-Clause */
/*
 * Copyright 2023,2024 nekosanteam <1688092+nekosanteam@users.noreply.github.com>. All Rights Reserved.
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
 * @file  asm_a64.hpp
 * @brief
 *
 */
#include <cstddef>
#include <cstdint>

namespace nk {
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

#define dsb_(ty) asm volatile("dsb" #ty : : : "memory")
#define dmb_(ty) asm volatile("dmb" #ty : : : "memory")

static inline void isb()
{
	asm volatile("isb sy" : : : "memory");
}

static inline void dsb()
{
	dsb_(sy);
}

static inline void mb()
{
	dmb_(sy);
}

static inline void rmb()
{
	dmb_(ld);
}

static inline void wmb()
{
	dmb_(st);
}

static inline void smp_mb()
{
	dmb_(ish);
}

static inline void smp_rmb()
{
	dmb_(ishld);
}

static inline void smp_wmb()
{
	dmb_(ishst);
}

static inline std::uint64_t MPIDR_EL1()
{
	std::uint64_t val;
	asm volatile("mrs %0, MPIDR_EL1" : : "r"(val));
	return val;
}

static inline std::uint64_t CurrentEL()
{
	std::uint64_t val;
	asm volatile("mrs %0, CurrentEL" : : "r"(val));
	return val;
}

static inline std::uint64_t get_scr_el3()
{
	std::uint64_t val;
	asm volatile("mrs %0, SCR_EL3" : "=r"(val));
	return val;
}

static inline void set_scr_el3(std::uint64_t val)
{
	asm volatile("msr SCR_EL3, %0" : : "r"(val));
}

// MMU (EL3/EL2)
static inline std::uint64_t get_ttbr0_el3()
{
	std::uint64_t val;
	asm volatile("mrs %0, TTBR0_EL3" : "=r"(val));
	return val;
}
static inline std::uint64_t get_tcr_el3()
{
	std::uint64_t val;
	asm volatile("mrs %0, TCR_EL3" : "=r"(val));
	return val;
}
static inline std::uint64_t get_tcr_el2()
{
	std::uint64_t val;
	asm volatile("mrs %0, TCR_EL2" : "=r"(val));
	return val;
}
static inline std::uint64_t get_vtcr_el2()
{
	std::uint64_t val;
	asm volatile("mrs %0, VTCR_EL2" : "=r"(val));
	return val;
}

static inline void set_ttbr0_el3(std::uint64_t val)
{
	asm volatile("msr TTBR0_EL3, %0" : : "r"(val));
}

static inline void set_tcr_el3(std::uint64_t val)
{
	asm volatile("msr TCR_EL3, %0" : : "r"(val));
}

static inline void set_tcr_el2(std::uint64_t val)
{
	asm volatile("msr TCR_EL2, %0" : : "r"(val));
}

static inline void set_vtcr_el2(std::uint64_t val)
{
	asm volatile("msr VTCR_EL2, %0" : : "r"(val));
}

// Vector Base Address
static inline std::uint64_t get_rvbar_el3()
{
	std::uint64_t val;
	asm volatile("mrs %0, RVBAR_EL3" : "=r"(val));
	return val;
}

static inline std::uint64_t get_vbar_el3()
{
	std::uint64_t val;
	asm volatile("mrs %0, VBAR_EL3" : "=r"(val));
	return val;
}

static inline std::uint64_t get_vbar_el2()
{
	std::uint64_t val;
	asm volatile("mrs %0, VBAR_EL2" : "=r"(val));
	return val;
}

static inline std::uint64_t get_vbar_el1()
{
	std::uint64_t val;
	asm volatile("mrs %0, VBAR_EL1" : "=r"(val));
	return val;
}

static inline void set_vbar_el3(std::uint64_t val)
{
	asm volatile("msr VBAR_EL3, %0" : : "r"(val));
}

static inline void set_vbar_el2(std::uint64_t val)
{
	asm volatile("msr VBAR_EL2, %0" : : "r"(val));
}

static inline void set_vbar_el1(std::uint64_t val)
{
	asm volatile("msr VBAR_EL1, %0" : : "r"(val));
}

} // namespace work
} // namespace nk
