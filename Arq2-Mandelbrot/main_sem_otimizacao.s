	.file	"main.cpp"
	.section	.text$_ZStorSt13_Ios_OpenmodeS_,"x"
	.linkonce discard
	.globl	__ZStorSt13_Ios_OpenmodeS_
	.def	__ZStorSt13_Ios_OpenmodeS_;	.scl	2;	.type	32;	.endef
__ZStorSt13_Ios_OpenmodeS_:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	orl	%edx, %eax
	popl	%ebp
	ret
.lcomm __ZStL8__ioinit,1,1
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "mandelbrot.ppm\0"
LC1:
	.ascii "P6\12%d\12%d\12"
	.ascii "255\12\0"
	.def	___gxx_personality_sj0;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Register;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Unregister;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	subl	$504, %esp
	movl	$___gxx_personality_sj0, -468(%ebp)
	movl	$LLSDA1111, -464(%ebp)
	leal	-460(%ebp), %eax
	leal	-24(%ebp), %edx
	movl	%edx, (%eax)
	movl	$L23, %edx
	movl	%edx, 4(%eax)
	movl	%esp, 8(%eax)
	leal	-492(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Register
	call	___main
	leal	-432(%ebp), %eax
	movl	$1, -488(%ebp)
	movl	%eax, %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEEC1Ev
	movl	$16, 4(%esp)
	movl	$4, (%esp)
	call	__ZStorSt13_Ios_OpenmodeS_
	leal	-432(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	movl	$2, -488(%ebp)
	movl	%edx, %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEE4openEPKcSt13_Ios_Openmode
	subl	$8, %esp
	movl	$1024, -84(%ebp)
	movl	$1024, -88(%ebp)
	movl	$20, (%esp)
	call	__Znaj
	movl	%eax, -92(%ebp)
	movl	$1024, 12(%esp)
	movl	$1024, 8(%esp)
	movl	$LC1, 4(%esp)
	movl	-92(%ebp), %eax
	movl	%eax, (%esp)
	call	_sprintf
	movl	-92(%ebp), %eax
	movl	%eax, (%esp)
	call	_strlen
	movl	%eax, %edx
	leal	-432(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	-92(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZNSo5writeEPKci
	subl	$8, %esp
	movl	-92(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZdlPv
	movl	$0, %eax
	movl	$-1073479680, %edx
	movl	%eax, -104(%ebp)
	movl	%edx, -100(%ebp)
	movl	$0, %eax
	movl	$1073217536, %edx
	movl	%eax, -112(%ebp)
	movl	%edx, -108(%ebp)
	movl	$0, %eax
	movl	$-1073741824, %edx
	movl	%eax, -120(%ebp)
	movl	%edx, -116(%ebp)
	movl	$0, %eax
	movl	$1073741824, %edx
	movl	%eax, -128(%ebp)
	movl	%edx, -124(%ebp)
	movl	$0, %eax
	movl	$1064304640, %edx
	movl	%eax, -136(%ebp)
	movl	%edx, -132(%ebp)
	movl	$0, %eax
	movl	$1064304640, %edx
	movl	%eax, -144(%ebp)
	movl	%edx, -140(%ebp)
	movl	$256, -148(%ebp)
	movl	$0, %eax
	movl	$1073741824, %edx
	movl	%eax, -160(%ebp)
	movl	%edx, -156(%ebp)
	movl	$0, %eax
	movl	$1074790400, %edx
	movl	%eax, -168(%ebp)
	movl	%edx, -164(%ebp)
	movl	$3145728, (%esp)
	call	__Znaj
	movl	%eax, -172(%ebp)
	movl	$0, -80(%ebp)
	movl	$0, -28(%ebp)
	jmp	L4
L19:
	fildl	-28(%ebp)
	fmull	-144(%ebp)
	fldl	LC5
	fsubrp	%st, %st(1)
	fstpl	-40(%ebp)
	fldl	-40(%ebp)
	fabs
	fldl	-144(%ebp)
	fldl	LC5
	fdivrp	%st, %st(1)
	fucompp
	fnstsw	%ax
	testb	$69, %ah
	jne	L5
L26:
	movl	$0, %eax
	movl	$0, %edx
	movl	%eax, -40(%ebp)
	movl	%edx, -36(%ebp)
L5:
	movl	$0, -32(%ebp)
	jmp	L7
L18:
	fildl	-32(%ebp)
	fmull	-136(%ebp)
	fldl	LC9
	fsubrp	%st, %st(1)
	fstpl	-184(%ebp)
	movl	$0, %eax
	movl	$0, %edx
	movl	%eax, -48(%ebp)
	movl	%edx, -44(%ebp)
	movl	$0, %eax
	movl	$0, %edx
	movl	%eax, -56(%ebp)
	movl	%edx, -52(%ebp)
	fldl	-48(%ebp)
	fmull	-48(%ebp)
	fstpl	-64(%ebp)
	fldl	-56(%ebp)
	fmull	-56(%ebp)
	fstpl	-72(%ebp)
	movl	$0, -76(%ebp)
	jmp	L8
L12:
	fldl	-48(%ebp)
	fadd	%st(0), %st
	fmull	-56(%ebp)
	faddl	-40(%ebp)
	fstpl	-56(%ebp)
	fldl	-64(%ebp)
	fsubl	-72(%ebp)
	faddl	-184(%ebp)
	fstpl	-48(%ebp)
	fldl	-48(%ebp)
	fmull	-48(%ebp)
	fstpl	-64(%ebp)
	fldl	-56(%ebp)
	fmull	-56(%ebp)
	fstpl	-72(%ebp)
	incl	-76(%ebp)
L8:
	cmpl	$255, -76(%ebp)
	jg	L9
	fldl	-64(%ebp)
	faddl	-72(%ebp)
	fldl	-168(%ebp)
	fucompp
	fnstsw	%ax
	testb	$69, %ah
	jne	L9
L27:
	movb	$1, %al
	jmp	L11
L9:
	movb	$0, %al
L11:
	testb	%al, %al
	jne	L12
	cmpl	$256, -76(%ebp)
	jne	L13
	movl	-80(%ebp), %edx
	movl	-172(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	movl	-80(%ebp), %eax
	leal	1(%eax), %edx
	movl	-172(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	movl	-80(%ebp), %eax
	leal	2(%eax), %edx
	movl	-172(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	addl	$3, -80(%ebp)
	jmp	L14
L13:
	movl	-80(%ebp), %edx
	movl	-172(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	$256, %eax
	subl	-76(%ebp), %eax
	andl	$-2147483641, %eax
	testl	%eax, %eax
	jns	L15
	decl	%eax
	orl	$-8, %eax
	incl	%eax
L15:
	movb	%al, %dl
	movb	%dl, %al
	sall	$6, %eax
	subl	%edx, %eax
	movb	%al, (%ecx)
	movl	-80(%ebp), %eax
	leal	1(%eax), %edx
	movl	-172(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	$256, %eax
	subl	-76(%ebp), %eax
	andl	$-2147483645, %eax
	testl	%eax, %eax
	jns	L16
	decl	%eax
	orl	$-4, %eax
	incl	%eax
L16:
	movb	%al, %dl
	movb	%dl, %al
	sall	$7, %eax
	subl	%edx, %eax
	movb	%al, (%ecx)
	movl	-80(%ebp), %eax
	leal	2(%eax), %edx
	movl	-172(%ebp), %eax
	addl	%eax, %edx
	movl	$256, %eax
	subl	-76(%ebp), %eax
	andl	$-2147483647, %eax
	testl	%eax, %eax
	jns	L17
	decl	%eax
	orl	$-2, %eax
	incl	%eax
L17:
	negl	%eax
	movb	%al, (%edx)
	addl	$3, -80(%ebp)
L14:
	incl	-32(%ebp)
L7:
	cmpl	$1023, -32(%ebp)
	setle	%al
	testb	%al, %al
	jne	L18
	incl	-28(%ebp)
L4:
	cmpl	$1023, -28(%ebp)
	setle	%al
	testb	%al, %al
	jne	L19
	leal	-432(%ebp), %eax
	movl	$3145728, 4(%esp)
	movl	-172(%ebp), %edx
	movl	%edx, (%esp)
	movl	$2, -488(%ebp)
	movl	%eax, %ecx
	call	__ZNSo5writeEPKci
	subl	$8, %esp
	leal	-432(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEE5closeEv
	movl	$0, -496(%ebp)
	leal	-432(%ebp), %eax
	movl	$1, -488(%ebp)
	movl	%eax, %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	movl	-496(%ebp), %eax
	movl	%eax, -500(%ebp)
	jmp	L28
L25:
	movl	%edx, -504(%ebp)
	leal	-432(%ebp), %eax
	movl	$0, -488(%ebp)
	movl	%eax, %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	movl	-504(%ebp), %eax
	jmp	L22
L23:
	leal	24(%ebp), %ebp
	movl	-484(%ebp), %edx
	movl	-488(%ebp), %eax
	testl	%eax, %eax
	je	L24
	cmpl	$1, %eax
	je	L25
		.word	0x0b0f
L24:
	movl	%edx, %eax
L22:
	movl	%eax, (%esp)
	movl	$-1, -488(%ebp)
	call	__Unwind_SjLj_Resume
L28:
	leal	-492(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Unregister
	movl	-500(%ebp), %eax
	leal	-16(%ebp), %esp
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.section	.gcc_except_table,"w"
LLSDA1111:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE1111-LLSDACSB1111
LLSDACSB1111:
	.uleb128 0
	.uleb128 0
	.uleb128 0x1
	.uleb128 0
LLSDACSE1111:
	.text
	.def	___tcf_0;	.scl	3;	.type	32;	.endef
___tcf_0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$__ZStL8__ioinit, %ecx
	call	__ZNSt8ios_base4InitD1Ev
	leave
	ret
	.def	__Z41__static_initialization_and_destruction_0ii;	.scl	3;	.type	32;	.endef
__Z41__static_initialization_and_destruction_0ii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	cmpl	$1, 8(%ebp)
	jne	L30
	cmpl	$65535, 12(%ebp)
	jne	L30
	movl	$__ZStL8__ioinit, %ecx
	call	__ZNSt8ios_base4InitC1Ev
	movl	$___tcf_0, (%esp)
	call	_atexit
L30:
	leave
	ret
	.def	__GLOBAL__sub_I_main;	.scl	3;	.type	32;	.endef
__GLOBAL__sub_I_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$65535, 4(%esp)
	movl	$1, (%esp)
	call	__Z41__static_initialization_and_destruction_0ii
	leave
	ret
	.section	.ctors,"w"
	.align 4
	.long	__GLOBAL__sub_I_main
	.section .rdata,"dr"
	.align 8
LC5:
	.long	0
	.long	1073741824
	.align 8
LC9:
	.long	0
	.long	1074003968
	.def	__Unwind_SjLj_Resume;	.scl	2;	.type	32;	.endef
	.def	__ZNSt14basic_ofstreamIcSt11char_traitsIcEEC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZNSt14basic_ofstreamIcSt11char_traitsIcEE4openEPKcSt13_Ios_Openmode;	.scl	2;	.type	32;	.endef
	.def	__Znaj;	.scl	2;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	__ZNSo5writeEPKci;	.scl	2;	.type	32;	.endef
	.def	__ZdlPv;	.scl	2;	.type	32;	.endef
	.def	__ZNSt14basic_ofstreamIcSt11char_traitsIcEE5closeEv;	.scl	2;	.type	32;	.endef
	.def	__ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	_atexit;	.scl	2;	.type	32;	.endef
