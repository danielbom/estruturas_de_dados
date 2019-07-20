	.file	"test_dict.c"
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
	.comm	d,8,8
	.text
	.globl	cmpInt
	.type	cmpInt, @function
cmpInt:
.LFB5:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR -40[rbp], rdi
	mov	QWORD PTR -48[rbp], rsi
	mov	edi, 4
	call	malloc@PLT
	mov	rdx, QWORD PTR -40[rbp]
	mov	edx, DWORD PTR [rdx]
	mov	DWORD PTR [rax], edx
	mov	QWORD PTR -16[rbp], rax
	mov	edi, 4
	call	malloc@PLT
	mov	rdx, QWORD PTR -48[rbp]
	mov	edx, DWORD PTR [rdx]
	mov	DWORD PTR [rax], edx
	mov	QWORD PTR -8[rbp], rax
	mov	rax, QWORD PTR -16[rbp]
	mov	edx, DWORD PTR [rax]
	mov	rax, QWORD PTR -8[rbp]
	mov	eax, DWORD PTR [rax]
	sub	edx, eax
	mov	eax, edx
	mov	DWORD PTR -20[rbp], eax
	mov	rax, QWORD PTR -16[rbp]
	mov	rdi, rax
	call	free@PLT
	mov	rax, QWORD PTR -8[rbp]
	mov	rdi, rax
	call	free@PLT
	mov	eax, DWORD PTR -20[rbp]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	cmpInt, .-cmpInt
	.section	.rodata
.LC0:
	.string	"New"
.LC1:
	.string	"Init %p\n"
	.text
	.globl	onInit
	.type	onInit, @function
onInit:
.LFB6:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	lea	rdi, .LC0[rip]
	call	puts@PLT
	mov	edi, 4
	call	dict_new@PLT
	mov	QWORD PTR d[rip], rax
	mov	rax, QWORD PTR d[rip]
	mov	rsi, rax
	lea	rdi, .LC1[rip]
	mov	eax, 0
	call	printf@PLT
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	onInit, .-onInit
	.section	.rodata
.LC2:
	.string	"Del"
	.text
	.globl	onDelete
	.type	onDelete, @function
onDelete:
.LFB7:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	lea	rdi, .LC2[rip]
	call	puts@PLT
	mov	rax, QWORD PTR d[rip]
	mov	rax, QWORD PTR 48[rax]
	lea	rdi, d[rip]
	call	rax
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	onDelete, .-onDelete
	.section	.rodata
.LC3:
	.string	"a"
.LC4:
	.string	"b"
.LC5:
	.string	"z"
.LC6:
	.string	"k"
.LC7:
	.string	"a: %d %d %p\n"
.LC8:
	.string	"aa"
.LC9:
	.string	"aa: %d %d %p\n"
.LC10:
	.string	"z: %d %d %p\n"
.LC11:
	.string	"b: %d %d %p\n"
.LC12:
	.string	"k: %d %d %p\n"
	.text
	.globl	test_1
	.type	test_1, @function
test_1:
.LFB8:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	eax, 0
	call	onInit
	mov	DWORD PTR -20[rbp], 0
	mov	rax, QWORD PTR d[rip]
	mov	rax, QWORD PTR 32[rax]
	mov	rcx, QWORD PTR d[rip]
	lea	rdx, -20[rbp]
	lea	rsi, .LC3[rip]
	mov	rdi, rcx
	call	rax
	mov	DWORD PTR -20[rbp], 100
	mov	rax, QWORD PTR d[rip]
	mov	rax, QWORD PTR 32[rax]
	mov	rcx, QWORD PTR d[rip]
	lea	rdx, -20[rbp]
	lea	rsi, .LC4[rip]
	mov	rdi, rcx
	call	rax
	mov	DWORD PTR -20[rbp], 40
	mov	rax, QWORD PTR d[rip]
	mov	rax, QWORD PTR 32[rax]
	mov	rcx, QWORD PTR d[rip]
	lea	rdx, -20[rbp]
	lea	rsi, .LC5[rip]
	mov	rdi, rcx
	call	rax
	mov	DWORD PTR -20[rbp], 900
	mov	rax, QWORD PTR d[rip]
	mov	rax, QWORD PTR 32[rax]
	mov	rcx, QWORD PTR d[rip]
	lea	rdx, -20[rbp]
	lea	rsi, .LC6[rip]
	mov	rdi, rcx
	call	rax
	mov	rax, QWORD PTR d[rip]
	mov	rax, QWORD PTR 40[rax]
	mov	rdx, QWORD PTR d[rip]
	lea	rsi, .LC3[rip]
	mov	rdi, rdx
	call	rax
	mov	QWORD PTR -16[rbp], rax
	cmp	QWORD PTR -16[rbp], 0
	je	.L6
	mov	rax, QWORD PTR -16[rbp]
	mov	eax, DWORD PTR [rax]
	jmp	.L7
.L6:
	mov	eax, -1
.L7:
	mov	rdx, QWORD PTR -16[rbp]
	mov	rcx, rdx
	mov	edx, eax
	mov	esi, 0
	lea	rdi, .LC7[rip]
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR d[rip]
	mov	rax, QWORD PTR 40[rax]
	mov	rdx, QWORD PTR d[rip]
	lea	rsi, .LC8[rip]
	mov	rdi, rdx
	call	rax
	mov	QWORD PTR -16[rbp], rax
	cmp	QWORD PTR -16[rbp], 0
	je	.L8
	mov	rax, QWORD PTR -16[rbp]
	mov	eax, DWORD PTR [rax]
	jmp	.L9
.L8:
	mov	eax, -1
.L9:
	mov	rdx, QWORD PTR -16[rbp]
	mov	rcx, rdx
	mov	edx, eax
	mov	esi, -1
	lea	rdi, .LC9[rip]
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR d[rip]
	mov	rax, QWORD PTR 40[rax]
	mov	rdx, QWORD PTR d[rip]
	lea	rsi, .LC5[rip]
	mov	rdi, rdx
	call	rax
	mov	QWORD PTR -16[rbp], rax
	cmp	QWORD PTR -16[rbp], 0
	je	.L10
	mov	rax, QWORD PTR -16[rbp]
	mov	eax, DWORD PTR [rax]
	jmp	.L11
.L10:
	mov	eax, -1
.L11:
	mov	rdx, QWORD PTR -16[rbp]
	mov	rcx, rdx
	mov	edx, eax
	mov	esi, 40
	lea	rdi, .LC10[rip]
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR d[rip]
	mov	rax, QWORD PTR 40[rax]
	mov	rdx, QWORD PTR d[rip]
	lea	rsi, .LC4[rip]
	mov	rdi, rdx
	call	rax
	mov	QWORD PTR -16[rbp], rax
	cmp	QWORD PTR -16[rbp], 0
	je	.L12
	mov	rax, QWORD PTR -16[rbp]
	mov	eax, DWORD PTR [rax]
	jmp	.L13
.L12:
	mov	eax, -1
.L13:
	mov	rdx, QWORD PTR -16[rbp]
	mov	rcx, rdx
	mov	edx, eax
	mov	esi, 100
	lea	rdi, .LC11[rip]
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR d[rip]
	mov	rax, QWORD PTR 40[rax]
	mov	rdx, QWORD PTR d[rip]
	lea	rsi, .LC6[rip]
	mov	rdi, rdx
	call	rax
	mov	QWORD PTR -16[rbp], rax
	cmp	QWORD PTR -16[rbp], 0
	je	.L14
	mov	rax, QWORD PTR -16[rbp]
	mov	eax, DWORD PTR [rax]
	jmp	.L15
.L14:
	mov	eax, -1
.L15:
	mov	rdx, QWORD PTR -16[rbp]
	mov	rcx, rdx
	mov	edx, eax
	mov	esi, 900
	lea	rdi, .LC12[rip]
	mov	eax, 0
	call	printf@PLT
	mov	eax, 0
	call	onDelete
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
.LFE8:
	.size	test_1, .-test_1
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	eax, 0
	call	test_1
	mov	eax, 0
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
