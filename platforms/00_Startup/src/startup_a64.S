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

#define STACK_SIZE 0x0800

#define BIT(n) (1<<(n))

#define CURRENTEL_EL3 (0x03 << 2)
#define CURRENTEL_EL2 (0x02 << 2)
#define CURRENTEL_EL1 (0x01 << 2)

#define SCTLR_EL3_RES1 (0x30C50838)
#define SCTLR_EL2_RES1 (0x30C50838)
#define SCTLR_EL1_RES1 (0x30D00990)
#define HCR_EL2_RES1   (0x00000002)

.global _start
.global _reset
.global __stack_top

	.align 4
_start:
	b	_reset

	.align 4
_reset:
	mrs	x0, CurrentEL
	cmp	x0, CURRENTEL_EL3
	b.eq	reset_at_el3
	cmp	x0, CURRENTEL_EL2
	b.eq	reset_at_el2
	cmp	x0, CURRENTEL_EL1
	b.eq	reset_at_el1
	b	.

/*
 * EL3 コード
 */
	.align 4
reset_at_el3:
	movz	x0, (((SCTLR_EL3_RES1) >>  0) & 0xffff)
	movk	x0, (((SCTLR_EL3_RES1) >> 16) & 0xffff), lsl #16
	msr	SCTLR_EL3, x0
	isb

	bl	setup_stack
	bl	cpu_init_baremetal
	bl	gic_secure_init
	b	start_boot_method
	b	.

/*
 * EL2 コード
 */
	.align 4
reset_at_el2:
	mov	x0, (((SCTLR_EL2_RES1) >>  0) & 0xffff)
	movk	x0, (((SCTLR_EL2_RES1) >> 16) & 0xffff), lsl #16
	msr	SCTLR_EL2, x0
	isb
	mov	x0, (((HCR_EL2_RES1) >>  0) & 0xffff)
	movk	x0, (((HCR_EL2_RES1) >> 16) & 0xffff), lsl #16
	msr	HCR_EL2, x0
	isb

	bl	setup_stack
	bl	start_boot_method
	b	.

/*
 * EL1 コード
 */
	.align 4
reset_at_el1:
	mov	x0, (((SCTLR_EL1_RES1) >>  0) & 0xffff)
	movk	x0, (((SCTLR_EL1_RES1) >> 16) & 0xffff), lsl #16
	msr	SCTLR_EL1, x0
	isb

	bl	setup_stack
	bl	start_boot_method
	b	.

;
	.align 4
setup_stack:
	ret

cpu_init_baremetal:
	ret

gic_secure_init:
	ret

start_boot_method:
	b	.

	// Initialize VBAR_ELn.
	ldr x1, =vector_table_el3
	msr VBAR_EL3, x1

//	ldr x1, =vector_table_el2
//	msr VBAR_EL2, x1

//	ldr x1, =vector_table_el1
//	msr VBAR_EL1, x1

	// Initialize stack pointer registers.
	adr x1, __stack_top
	add x1, x1, #4
	mrs x2, MPIDR_EL1
	and x2, x2, #0xFF // X2 == CPU number.
	mov x3, #STACK_SIZE
	mul x3, x2, x3
	sub x1, x1, x3
	mov sp, x1

	// Initialize system control regisers.
	msr HCR_EL2, XZR
	ldr x1, =0x30C50838
	msr SCTLR_EL2, x1
	msr SCTLR_EL1, x1

	bl main
	b .

_enable_async_exceptions_toEL3:
	// Enable Asynchronous Exceptions to EL3.
	mrs x0, SCR_EL3
	orr x0, x0, #(1<<3) // EA bit.
	orr x0, x0, #(1<<1) // IRQ bit.
	orr x0, x0, #(1<<2) // FIQ bit.
	msr SCR_EL3, x0
	ret

_enable_async_exceptions_toEL2:
	// Enable Asynchronous Exceptions to EL2.
	mrs x0, HCR_EL2
	orr x0, x0, #(1<<5) // AMO bit.
	orr x0, x0, #(1<<4) // IMO bit.
	orr x0, x0, #(1<<3) // FMO bit.
	msr HCR_EL2, x0
	ret

_enable_exceptions:
	// Enable SError, IRQ and FIQ.
	msr DAIFClr, #0x07
	ret

_disable_l1_caches:
	// Disable L1 Caches
	mrs x0, SCTLR_EL3
	bic x0, x0, #(1<<2)
	msr SCTLR_EL3, x0
	ret

_invalidate_dcache:
	// Invalidate Data Cache.
	mov x0, #0x0
	msr CSSELR_EL1, x0

	mrs x4, CCSIDR_EL1
	and x1, x4, #0x07
	add x1, x1, #0x04
	ldr x3, =0x7FFF
	and x2, x3, x4, LSR #13
	ldr x3, =0x3FF
	and x3, x3, x4, LSR #3
	clz w4, w3

	mov x5, #0x0
way_loop:
	mov x6, #0x0
set_loop:
	lsl x7, x5, x4
	orr x7, x0, x7
	lsl x8, x6, x1
	orr x7, x7, x8
	dc  cisw, x7
	add x6, x6, #1
	cmp x6, x2
	ble set_loop
	add x5, x5, #1
	cmp x5, x3
	ble way_loop
	ret    

	.align 11
vector_table_el3:
curr_el_sp0_sync:
	ret

	.align 7
curr_el_sp0_irq:
	ret

	.align 7
curr_el_sp0_fiq:
	ret

	.align 7
curr_el_sp0_serror:
	ret

	.align 7
curr_el_spx_sync:
	ret

	.align 7
curr_el_spx_irq:
	ret

	.align 7
curr_el_spx_fiq:
	ret

	.align 7
curr_el_spx_serror:
	ret

	.align 7
lower_el_aarch64_sync:
	ret

	.align 7
lower_el_aarch64_irq:
	ret

	.align 7
lower_el_aarch64_fiq:
	ret

	.align 7
lower_el_aarch64_serror:
	ret

	.align 7
lower_el_aarch32_sync:
	ret

	.align 7
lower_el_aarch32_irq:
	ret

	.align 7
lower_el_aarch32_fiq:
	ret

	.align 7
lower_el_aarch32_serror:
	ret

	.align 11
vector_table_el2:
	ret

	.align 11
vector_table_el1:
	ret
