	.file	"MultiThread_Mutex.c"
	.comm	fd,4,4
	.comm	text,4,1
	.comm	thrd,16,16
	.comm	tattr,56,32
	.section	.rodata
.LC0:
	.string	"exit"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	open_func
	movl	$0, %eax
	call	thread_func
.L4:
	movq	stdin(%rip), %rax
	movq	%rax, %rdx
	movl	$4, %esi
	movl	$text, %edi
	call	fgets
	movl	$4, %edx
	movl	$.LC0, %esi
	movl	$text, %edi
	call	strncmp
	testl	%eax, %eax
	jne	.L7
	movl	$text, %edi
	call	puts
	movl	$1, %edi
	movl	$0, %eax
	call	sleep
	jmp	.L4
.L7:
	nop
	movl	fd(%rip), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	close
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata
.LC1:
	.string	"development_file"
.LC2:
	.string	"open"
	.text
	.globl	open_func
	.type	open_func, @function
open_func:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$66, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	open
	movl	%eax, fd(%rip)
	movl	fd(%rip), %eax
	cmpl	$-1, %eax
	jne	.L10
	movl	$.LC2, %edi
	call	perror
	movl	$1, %edi
	call	exit
.L10:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	open_func, .-open_func
	.section	.rodata
.LC3:
	.string	"pthread_attr_init"
.LC4:
	.string	"pthread_attr_setdetachstate"
	.text
	.globl	thread_func
	.type	thread_func, @function
thread_func:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$tattr, %edi
	call	pthread_attr_init
	testl	%eax, %eax
	je	.L12
	movl	$.LC3, %edi
	call	perror
	movl	$1, %edi
	call	exit
.L12:
	movl	$1, %esi
	movl	$tattr, %edi
	call	pthread_attr_setdetachstate
	testl	%eax, %eax
	je	.L13
	movl	$.LC4, %edi
	call	perror
	movl	$1, %edi
	call	exit
.L13:
	leaq	-4(%rbp), %rax
	movq	%rax, %rcx
	movl	$thread_read, %edx
	movl	$tattr, %esi
	movl	$thrd, %edi
	call	pthread_create
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	thread_func, .-thread_func
	.section	.rodata
.LC5:
	.string	"read"
.LC6:
	.string	"i'm in the read thread"
	.text
	.globl	thread_read
	.type	thread_read, @function
thread_read:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
.L16:
	movl	$4, %edx
	movl	$.LC5, %esi
	movl	$text, %edi
	call	strncmp
	testl	%eax, %eax
	je	.L16
	movl	$.LC6, %edi
	call	puts
	movl	$4, %edx
	movl	$48, %esi
	movl	$text, %edi
	call	memset
	jmp	.L16
	.cfi_endproc
.LFE5:
	.size	thread_read, .-thread_read
	.ident	"GCC: (GNU) 6.3.1 20161221 (Red Hat 6.3.1-1)"
	.section	.note.GNU-stack,"",@progbits
