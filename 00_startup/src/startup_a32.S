@ startup
        .global _start
        .align
_start:
        // set stack pointer for SVC mode.
        // IRQ, FIQ disable, Thumb disable, SVC mode.
        ldr     r0, =0x000000d3
        msr     cpsr, r0
        ldr     sp, =0x06400000

        bl      main
        b       .
    