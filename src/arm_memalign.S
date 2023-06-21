	.text
	.align	2
	.global	memalign_alloc
	.type	memalign_alloc, %function
memalign_alloc:
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-28]
	add	r3, r2, r3
	add	r3, r3, #4
	mov	r0, r3
	bl	malloc
	mov	r3, r0
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bne	.L2
	mov	r3, #0
	b	.L3
.L2:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-24]
	add	r3, r2, r3
	add	r2, r3, #4
	ldr	r3, [fp, #-24]
	rsb	r3, r3, #0
	and	r3, r3, r2
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-12]
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-16]
	sub	r3, r3, #4
	ldr	r2, [fp, #-8]
	str	r2, [r3]
	ldr	r3, [fp, #-12]
.L3:
	mov	r0, r3
	sub	sp, fp, #4
	pop	{fp, pc}
	.size	memalign_alloc, .-memalign_alloc
	.align	2
	.global	memalign_free
	.type	memalign_free, %function
memalign_free:
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	ldr	r3, [fp, #-16]
	cmp	r3, #0
	beq	.L5
	ldr	r3, [fp, #-16]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	sub	r3, r3, #4
	ldr	r3, [r3]
	mov	r0, r3
	bl	free
	b	.L4
.L5:
	nop
.L4:
	sub	sp, fp, #4
	pop	{fp, pc}
	.size	memalign_free, .-memalign_free
	.align	2
	.global	memalign_alloc_aligned
	.type	memalign_alloc_aligned, %function
memalign_alloc_aligned:
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	ldr	r1, [fp, #-8]
	mov	r0, #32
	bl	memalign_alloc
	mov	r3, r0
	mov	r0, r3
	sub	sp, fp, #4
	pop	{fp, pc}
	.size	memalign_alloc_aligned, .-memalign_alloc_aligned
