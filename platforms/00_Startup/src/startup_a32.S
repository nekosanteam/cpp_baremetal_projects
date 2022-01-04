@ startup
.global _start
.global __stack_top

	.text
	.align
_start:
	// set stack pointer for SVC mode.
	// IRQ, FIQ disable, Thumb disable, SVC mode.
	ldr     r0, =0x000000d3
	msr     cpsr, r0
	ldr     sp, =__stack_top

	bl      main
	b       .
