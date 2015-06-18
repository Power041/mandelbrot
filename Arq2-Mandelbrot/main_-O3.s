	.file	"main.cpp"
	.text
	.p2align 2,,3
	.def	___tcf_0;	.scl	3;	.type	32;	.endef
___tcf_0:
	movl	$__ZStL8__ioinit, %ecx
	jmp	__ZNSt8ios_base4InitD1Ev
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC2:
	.ascii "mandelbrot.ppm\0"
LC3:
	.ascii "P6\12%d\12%d\12"
	.ascii "255\12\0"
	.def	___gxx_personality_sj0;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Register;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Unregister;	.scl	2;	.type	32;	.endef
	.section	.text.startup,"x"
	.p2align 2,,3
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
	subl	$360, %esp
	movl	$___gxx_personality_sj0, -308(%ebp)
	movl	$LLSDA1176, -304(%ebp)
	leal	-24(%ebp), %eax
	movl	%eax, -300(%ebp)
	movl	$L14, -296(%ebp)
	movl	%esp, -292(%ebp)
	leal	-332(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Register
	call	___main
	movl	$-1, -328(%ebp)
	leal	-272(%ebp), %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEEC1Ev
	movl	$20, 4(%esp)
	movl	$LC2, (%esp)
	movl	$1, -328(%ebp)
	leal	-272(%ebp), %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEE4openEPKcSt13_Ios_Openmode
	subl	$8, %esp
	movl	$20, (%esp)
	call	__Znaj
	movl	%eax, -344(%ebp)
	movl	$1024, 12(%esp)
	movl	$1024, 8(%esp)
	movl	$LC3, 4(%esp)
	movl	%eax, (%esp)
	call	_sprintf
	xorl	%eax, %eax
	movl	$-1, %ecx
	movl	-344(%ebp), %edi
	repne scasb
	notl	%ecx
	decl	%ecx
	movl	%ecx, 4(%esp)
	movl	-344(%ebp), %eax
	movl	%eax, (%esp)
	leal	-272(%ebp), %ecx
	call	__ZNSo5writeEPKci
	subl	$8, %esp
	movl	-344(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZdlPv
	movl	$3145728, (%esp)
	call	__Znaj
	movl	%eax, -352(%ebp)
	movl	$3, -348(%ebp)
	movl	$0, -336(%ebp)
	flds	LC1
	fstpl	-344(%ebp)
	subl	$3, %eax
	movl	%eax, -356(%ebp)
	movl	%eax, %edx
L3:
	addl	-348(%ebp), %edx
	xorl	%ecx, %ecx
	movl	$256, %edi
	movl	%ecx, %esi
	jmp	L7
	.p2align 2,,3
L24:
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	movb	$0, (%edx)
	movb	$0, 1(%edx)
	movb	$0, 2(%edx)
	incl	%esi
	addl	$3, %edx
	cmpl	$1024, %esi
	je	L23
L7:
	fldl	LC9
	pushl	%esi
	fimull	(%esp)
	popl	%eax
	fsubs	LC7
	xorl	%ebx, %ebx
	fldz
	fld	%st(0)
	fld	%st(1)
	fld	%st(2)
	flds	LC8
	fxch	%st(4)
	jmp	L5
	.p2align 2,,3
L26:
	fxch	%st(3)
	fxch	%st(1)
	fxch	%st(2)
L5:
	fadd	%st(0), %st
	fmulp	%st, %st(1)
	faddl	-344(%ebp)
	fxch	%st(1)
	fsubp	%st, %st(2)
	fxch	%st(1)
	fadd	%st(3), %st
	fld	%st(0)
	fmul	%st(1), %st
	fld	%st(2)
	fmul	%st(3), %st
	incl	%ebx
	cmpl	$256, %ebx
	je	L24
	fld	%st(1)
	fadd	%st(1), %st
	fld	%st(5)
	fucompp
	fnstsw	%ax
	testb	$69, %ah
	je	L26
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	movl	%edi, %eax
	subl	%ebx, %eax
	movl	%eax, %ebx
	movb	%al, %cl
	andl	$7, %ecx
	movb	%cl, %al
	sall	$6, %eax
	subl	%ecx, %eax
	movb	%al, (%edx)
	movb	%bl, %cl
	andl	$3, %ecx
	movb	%cl, %al
	sall	$7, %eax
	subl	%ecx, %eax
	movb	%al, 1(%edx)
	andl	$1, %ebx
	negl	%ebx
	movb	%bl, 2(%edx)
	incl	%esi
	addl	$3, %edx
	cmpl	$1024, %esi
	jne	L7
L23:
	incl	-336(%ebp)
	cmpl	$1024, -336(%ebp)
	je	L25
	flds	LC4
	fimull	-336(%ebp)
	fsubs	LC5
	fstl	-344(%ebp)
	fabs
	flds	LC6
	fucompp
	fnstsw	%ax
	testb	$69, %ah
	jne	L4
	fldz
	fstpl	-344(%ebp)
L4:
	addl	$3072, -348(%ebp)
	movl	-356(%ebp), %edx
	jmp	L3
L25:
	movl	$3145728, 4(%esp)
	movl	-352(%ebp), %eax
	movl	%eax, (%esp)
	movl	$1, -328(%ebp)
	leal	-272(%ebp), %ecx
	call	__ZNSo5writeEPKci
	subl	$8, %esp
	leal	-272(%ebp), %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEE5closeEv
	movl	$-1, -328(%ebp)
	leal	-272(%ebp), %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	leal	-332(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Unregister
	xorl	%eax, %eax
	leal	-16(%ebp), %esp
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
L14:
	addl	$24, %ebp
	movl	-324(%ebp), %eax
	movl	%eax, -344(%ebp)
	movl	$0, -328(%ebp)
	leal	-272(%ebp), %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	movl	-344(%ebp), %eax
	movl	%eax, (%esp)
	movl	$-1, -328(%ebp)
	call	__Unwind_SjLj_Resume
	.section	.gcc_except_table,"w"
LLSDA1176:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE1176-LLSDACSB1176
LLSDACSB1176:
	.uleb128 0
	.uleb128 0
LLSDACSE1176:
	.section	.text.startup,"x"
	.p2align 2,,3
	.def	__GLOBAL__sub_I_main;	.scl	3;	.type	32;	.endef
__GLOBAL__sub_I_main:
	subl	$28, %esp
	movl	$__ZStL8__ioinit, %ecx
	call	__ZNSt8ios_base4InitC1Ev
	movl	$___tcf_0, (%esp)
	call	_atexit
	addl	$28, %esp
	ret
	.section	.ctors,"w"
	.align 4
	.long	__GLOBAL__sub_I_main
.lcomm __ZStL8__ioinit,1,1
	.section .rdata,"dr"
	.align 4
LC1:
	.long	-1073741824
	.align 4
LC4:
	.long	998244352
	.align 4
LC5:
	.long	1073741824
	.align 4
LC6:
	.long	989855744
	.align 4
LC7:
	.long	1075838976
	.align 4
LC8:
	.long	1082130432
	.align 8
LC9:
	.long	0
	.long	1064304640
	.def	__ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Resume;	.scl	2;	.type	32;	.endef
	.def	__ZNSt14basic_ofstreamIcSt11char_traitsIcEEC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZNSt14basic_ofstreamIcSt11char_traitsIcEE4openEPKcSt13_Ios_Openmode;	.scl	2;	.type	32;	.endef
	.def	__Znaj;	.scl	2;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	__ZNSo5writeEPKci;	.scl	2;	.type	32;	.endef
	.def	__ZdlPv;	.scl	2;	.type	32;	.endef
	.def	__ZNSt14basic_ofstreamIcSt11char_traitsIcEE5closeEv;	.scl	2;	.type	32;	.endef
	.def	__ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	_atexit;	.scl	2;	.type	32;	.endef
