	.file	"multboot.c"
	.comm	magic,4,4
	.globl	mbh
	.section	.text,"aw",@progbits
	.align 4
	.type	mbh, @object
	.size	mbh, 12
mbh:
	.long	464367618
	.long	3
	.long	-464367621
	.section	.rodata
.LC0:
	.string	"Kernel load error!\n"
.LC1:
	.string	"Hello world!\n"
	.text
	.globl	KernelEntry
	.type	KernelEntry, @function
KernelEntry:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
#APP
# 17 "multboot.c" 1
	movl %eax,magic
# 0 "" 2
#NO_APP
	movl	magic, %eax
	cmpl	$464367618, %eax
	je	.L2
	subl	$12, %esp
	pushl	$.LC0
	call	mbprint
	addl	$16, %esp
.L3:
	jmp	.L3
.L2:
	subl	$12, %esp
	pushl	$.LC1
	call	mbprint
	addl	$16, %esp
.L4:
	jmp	.L4
	.cfi_endproc
.LFE0:
	.size	KernelEntry, .-KernelEntry
	.globl	mbprint
	.type	mbprint, @function
mbprint:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$753664, -4(%ebp)
	jmp	.L6
.L7:
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	movl	8(%ebp), %edx
	leal	1(%edx), %ecx
	movl	%ecx, 8(%ebp)
	movzbl	(%edx), %edx
	movb	%dl, (%eax)
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	movb	$4, (%eax)
.L6:
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$10, %al
	jne	.L7
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	mbprint, .-mbprint
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits
