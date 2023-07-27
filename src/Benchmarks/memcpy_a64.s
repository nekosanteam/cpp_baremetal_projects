	.arch armv8-a
	.file	"memcpy_a64.cpp"
	.text
	.align	2
	.p2align 3,,7
	.global	_Z16memcpy16b_burstNPvS_j
	.type	_Z16memcpy16b_burstNPvS_j, %function
_Z16memcpy16b_burstNPvS_j:
.LFB3:
	.cfi_startproc
	cmp	w2, 2
	mov	x3, x0
	beq	.L2
	cmp	w2, 4
	beq	.L3
	cmp	w2, 1
	mov	x0, 0
	beq	.L7
	ret
	.p2align 2,,3
.L7:
#APP
// 17 "memcpy_a64.cpp" 1
	ldp x1, x0, [x1]
	stp x1, x0, [x3]
// 0 "" 2
#NO_APP
	mov	x0, x3
	ret
	.p2align 2,,3
.L3:
#APP
// 42 "memcpy_a64.cpp" 1
	ld1 {v0.16b-v3.16b}, [x1]
	st1 {v0.16b-v3.16b}, [x0]
// 0 "" 2
#NO_APP
	ret
	.p2align 2,,3
.L2:
#APP
// 31 "memcpy_a64.cpp" 1
	ldp q0, q2, [x1]
	stp q0, q2, [x0]
// 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE3:
	.size	_Z16memcpy16b_burstNPvS_j, .-_Z16memcpy16b_burstNPvS_j
	.align	2
	.p2align 3,,7
	.global	_Z9memcpy16bPvS_m
	.type	_Z9memcpy16bPvS_m, %function
_Z9memcpy16bPvS_m:
.LFB4:
	.cfi_startproc
	add	x2, x2, 15
	cmp	xzr, x2, lsr 4
	lsr	x2, x2, 4
	beq	.L9
	add	x3, x0, x2, lsl 4
	mov	x2, x0
	.p2align 3,,7
.L10:
#APP
// 17 "memcpy_a64.cpp" 1
	ldp x4, x5, [x1]
	stp x4, x5, [x2]
// 0 "" 2
#NO_APP
	add	x2, x2, 16
	add	x1, x1, 16
	cmp	x3, x2
	bne	.L10
.L9:
	ret
	.cfi_endproc
.LFE4:
	.size	_Z9memcpy16bPvS_m, .-_Z9memcpy16bPvS_m
	.align	2
	.p2align 3,,7
	.global	_Z9memcpy32bPvS_m
	.type	_Z9memcpy32bPvS_m, %function
_Z9memcpy32bPvS_m:
.LFB5:
	.cfi_startproc
	add	x2, x2, 31
	cmp	xzr, x2, lsr 5
	lsr	x2, x2, 5
	beq	.L16
	add	x3, x0, x2, lsl 5
	mov	x2, x0
	.p2align 3,,7
.L17:
#APP
// 31 "memcpy_a64.cpp" 1
	ldp q0, q2, [x1]
	stp q0, q2, [x2]
// 0 "" 2
#NO_APP
	add	x2, x2, 32
	add	x1, x1, 32
	cmp	x3, x2
	bne	.L17
.L16:
	ret
	.cfi_endproc
.LFE5:
	.size	_Z9memcpy32bPvS_m, .-_Z9memcpy32bPvS_m
	.align	2
	.p2align 3,,7
	.global	_Z9memcpy64bPvS_m
	.type	_Z9memcpy64bPvS_m, %function
_Z9memcpy64bPvS_m:
.LFB6:
	.cfi_startproc
	add	x2, x2, 63
	cmp	xzr, x2, lsr 6
	lsr	x2, x2, 6
	beq	.L23
	add	x3, x0, x2, lsl 6
	mov	x2, x0
	.p2align 3,,7
.L24:
#APP
// 42 "memcpy_a64.cpp" 1
	ld1 {v0.16b-v3.16b}, [x1]
	st1 {v0.16b-v3.16b}, [x2]
// 0 "" 2
#NO_APP
	add	x2, x2, 64
	add	x1, x1, 64
	cmp	x3, x2
	bne	.L24
.L23:
	ret
	.cfi_endproc
.LFE6:
	.size	_Z9memcpy64bPvS_m, .-_Z9memcpy64bPvS_m
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
