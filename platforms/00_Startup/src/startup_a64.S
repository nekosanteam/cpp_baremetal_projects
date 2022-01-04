#define STACK_SIZE 0x0800

.global _start
.global __stack_top

	.align
_start:

    // Initialize VBAR_ELn.
    ldr x1, =vector_table_el3
    msr VBAR_EL3, x1

    ldr x1, =vector_table_el2
    msr VBAR_EL2, x1

    ldr x1, =vector_table_el1
    msr VBAR_EL1, x1

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

.balign 0x0800
vector_table_el3:
curr_el_sp0_sync:

.balign 0x0080
curr_el_sp0_irq:

.balign 0x0080
curr_el_sp0_fiq:

.balign 0x0080
curr_el_sp0_serror:

.balign 0x0080
curr_el_spx_sync:

.balign 0x0080
curr_el_spx_irq:

.balign 0x0080
curr_el_spx_fiq:

.balign 0x0080
curr_el_spx_serror:

.balign 0x0080
lower_el_aarch64_sync:

.balign 0x0080
lower_el_aarch64_irq:

.balign 0x0080
lower_el_aarch64_fiq:

.balign 0x0080
lower_el_aarch64_serror:

.balign 0x0080
lower_el_aarch32_sync:

.balign 0x0080
lower_el_aarch32_irq:

.balign 0x0080
lower_el_aarch32_fiq:

.balign 0x0080
lower_el_aarch32_serror:

.balign 0x0800
vector_table_el2:

.balign 0x0800
vector_table_el1:
