	.file	"dict_t.c"
	.intel_syntax noprefix
	.text
	.section	.data.rel.ro,"aw",@progbits
	.align 32
	.type	Array, @object
	.size	Array, 120
Array:
	.quad	0
	.quad	0
	.quad	0
	.quad	0
	.quad	array_new
	.quad	array_init
	.quad	array_del
	.quad	array_append
	.quad	array_set
	.quad	array_insert
	.quad	array_insort
	.quad	array_get
	.quad	array_bsearch
	.quad	array_fatten
	.quad	array_length
	.section	.data.rel.ro.local,"aw",@progbits
	.align 32
	.type	Dict, @object
	.size	Dict, 56
Dict:
	.quad	0
	.quad	0
	.quad	dict_new
	.quad	dict_init
	.quad	dict_set
	.quad	dict_get
	.quad	dict_del
	.section	.rodata
.LC0:
	.string	"%p %p %p\n"
	.align 8
.LC1:
	.string	"You need call [dict]->init to configure this values."
.LC2:
	.string	"dict ERROR!!!\n"
	.text
	.globl	dict_assertion
	.type	dict_assertion, @function
dict_assertion:
.LFB5:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR -8[rbp], rdi
	cmp	QWORD PTR -8[rbp], 0
	je	.L2
	mov	rax, QWORD PTR -8[rbp]
	mov	rax, QWORD PTR [rax]
	test	rax, rax
	je	.L2
	mov	rax, QWORD PTR -8[rbp]
	mov	rax, QWORD PTR 8[rax]
	test	rax, rax
	jne	.L4
.L2:
	mov	rax, QWORD PTR -8[rbp]
	mov	rcx, QWORD PTR 8[rax]
	mov	rax, QWORD PTR -8[rbp]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR -8[rbp]
	mov	rsi, rax
	lea	rdi, .LC0[rip]
	mov	eax, 0
	call	printf@PLT
	lea	rdi, .LC1[rip]
	call	puts@PLT
	lea	rdi, .LC2[rip]
	call	perror@PLT
	mov	edi, -1
	call	exit@PLT
.L4:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	dict_assertion, .-dict_assertion
	.globl	dict_key_cmp
	.type	dict_key_cmp, @function
dict_key_cmp:
.LFB6:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR -8[rbp], rdi
	mov	QWORD PTR -16[rbp], rsi
	mov	rdx, QWORD PTR -16[rbp]
	mov	rax, QWORD PTR -8[rbp]
	mov	rsi, rdx
	mov	rdi, rax
	call	strcmp@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	dict_key_cmp, .-dict_key_cmp
	.globl	dict_get
	.type	dict_get, @function
dict_get:
.LFB7:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR -40[rbp], rdi
	mov	QWORD PTR -48[rbp], rsi
	mov	rax, QWORD PTR -40[rbp]
	mov	rdi, rax
	call	dict_assertion
	mov	rax, QWORD PTR -40[rbp]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR -24[rbp], rax
	mov	rax, QWORD PTR -40[rbp]
	mov	rax, QWORD PTR 8[rax]
	mov	QWORD PTR -16[rbp], rax
	mov	rax, QWORD PTR -24[rbp]
	mov	rax, QWORD PTR 96[rax]
	mov	rsi, QWORD PTR -48[rbp]
	mov	rcx, QWORD PTR -24[rbp]
	lea	rdx, dict_key_cmp[rip]
	mov	rdi, rcx
	call	rax
	mov	QWORD PTR -8[rbp], rax
	cmp	QWORD PTR -8[rbp], -1
	jne	.L8
	mov	eax, 0
	jmp	.L9
.L8:
	mov	rax, QWORD PTR -16[rbp]
	mov	rax, QWORD PTR 88[rax]
	mov	rcx, QWORD PTR -8[rbp]
	mov	rdx, QWORD PTR -16[rbp]
	mov	rsi, rcx
	mov	rdi, rdx
	call	rax
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	dict_get, .-dict_get
	.globl	dict_set
	.type	dict_set, @function
dict_set:
.LFB8:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 72
	.cfi_offset 3, -24
	mov	QWORD PTR -56[rbp], rdi
	mov	QWORD PTR -64[rbp], rsi
	mov	QWORD PTR -72[rbp], rdx
	mov	rax, QWORD PTR -56[rbp]
	mov	rdi, rax
	call	dict_assertion
	mov	rax, QWORD PTR -56[rbp]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR -40[rbp], rax
	mov	rax, QWORD PTR -56[rbp]
	mov	rax, QWORD PTR 8[rax]
	mov	QWORD PTR -32[rbp], rax
	mov	rax, QWORD PTR -40[rbp]
	mov	rax, QWORD PTR 96[rax]
	mov	rsi, QWORD PTR -64[rbp]
	mov	rcx, QWORD PTR -40[rbp]
	lea	rdx, dict_key_cmp[rip]
	mov	rdi, rcx
	call	rax
	mov	QWORD PTR -24[rbp], rax
	cmp	QWORD PTR -24[rbp], -1
	jne	.L11
	mov	rax, QWORD PTR -40[rbp]
	mov	rbx, QWORD PTR 80[rax]
	mov	rax, QWORD PTR -64[rbp]
	mov	rdi, rax
	call	strdup@PLT
	mov	rcx, rax
	mov	rax, QWORD PTR -40[rbp]
	lea	rdx, dict_key_cmp[rip]
	mov	rsi, rcx
	mov	rdi, rax
	call	rbx
	mov	QWORD PTR -24[rbp], rax
	mov	rax, QWORD PTR -32[rbp]
	mov	rax, QWORD PTR 72[rax]
	mov	rdx, QWORD PTR -24[rbp]
	mov	rsi, QWORD PTR -72[rbp]
	mov	rcx, QWORD PTR -32[rbp]
	mov	rdi, rcx
	call	rax
.L11:
	mov	rax, QWORD PTR -56[rbp]
	add	rsp, 72
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	dict_set, .-dict_set
	.globl	dict_init
	.type	dict_init, @function
dict_init:
.LFB9:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR -8[rbp], rdi
	mov	QWORD PTR -16[rbp], rsi
	mov	rax, QWORD PTR -8[rbp]
	mov	edx, 56
	lea	rsi, Dict[rip]
	mov	rdi, rax
	call	memcpy@PLT
	mov	esi, 64
	mov	edi, 8
	call	array_new@PLT
	mov	rdx, rax
	mov	rax, QWORD PTR -8[rbp]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR -16[rbp]
	mov	esi, 64
	mov	rdi, rax
	call	array_new@PLT
	mov	rdx, rax
	mov	rax, QWORD PTR -8[rbp]
	mov	QWORD PTR 8[rax], rdx
	mov	rax, QWORD PTR -8[rbp]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	dict_init, .-dict_init
	.globl	dict_del
	.type	dict_del, @function
dict_del:
.LFB10:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR -40[rbp], rdi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	rax, QWORD PTR -40[rbp]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR -16[rbp], rax
	mov	rax, QWORD PTR -16[rbp]
	mov	rdi, rax
	call	dict_assertion
	mov	rax, QWORD PTR -16[rbp]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR -32[rbp], rax
	mov	rax, QWORD PTR -32[rbp]
	mov	rax, QWORD PTR 48[rax]
	lea	rdx, -32[rbp]
	mov	rdi, rdx
	call	rax
	mov	rax, QWORD PTR -16[rbp]
	mov	rax, QWORD PTR 8[rax]
	mov	QWORD PTR -24[rbp], rax
	mov	rax, QWORD PTR -24[rbp]
	mov	rax, QWORD PTR 48[rax]
	lea	rdx, -24[rbp]
	mov	rdi, rdx
	call	rax
	mov	rax, QWORD PTR -40[rbp]
	mov	rax, QWORD PTR [rax]
	mov	rdi, rax
	call	free@PLT
	mov	rax, QWORD PTR -40[rbp]
	mov	QWORD PTR [rax], 0
	nop
	mov	rax, QWORD PTR -8[rbp]
	xor	rax, QWORD PTR fs:40
	je	.L16
	call	__stack_chk_fail@PLT
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	dict_del, .-dict_del
	.globl	dict_new
	.type	dict_new, @function
dict_new:
.LFB11:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR -8[rbp], rdi
	mov	edi, 56
	call	malloc@PLT
	mov	rdx, rax
	mov	rax, QWORD PTR -8[rbp]
	mov	rsi, rax
	mov	rdi, rdx
	call	dict_init
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	dict_new, .-dict_new
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
