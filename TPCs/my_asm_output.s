# xvalue = xmm15
# yvalue = xmm14
# iteration = rax
# zi = xmm12
# zr = xmm13
#


computePoint:
	movsd	%xmm0, xvalue
	movsd	%xmm1, yvalue
	movl	$0, iteration
	pxor	%xmm0, %xmm0
	movsd	%xmm0, zi
	pxor	%xmm0, %xmm0
	movsd	%xmm0, zr
	jmp	.while_signature
.while_body:
	movsd	zr, %xmm0
	movapd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	movsd	zi, %xmm0
	movapd	%xmm0, %xmm2
	mulsd	%xmm0, %xmm2
	subsd	%xmm2, %xmm1
	movapd	%xmm1, %xmm0
	movsd	xvalue, %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, reg6
	movsd	zr, %xmm0
	addsd	%xmm0, %xmm0
	mulsd	zi, %xmm0
	movsd	yvalue, %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, reg8
	movsd	reg8, %xmm0
	movsd	%xmm0, zi
	movsd	reg6, %xmm0
	movsd	%xmm0, zr
	addl	$1, iteration
.while_signature:
	movsd	zr, %xmm0			#  xmm0 = zr
	movapd	%xmm0, %xmm1		#  xmm1 = zr
	mulsd	%xmm0, %xmm1		#  xmm1 = zr * zr
	movsd	zi, %xmm0			#  xmm0 = zi
	mulsd	%xmm0, %xmm0 		#  xmm0 = zi * zi
	addsd	%xmm0, %xmm1		#  xmm1 = zr * zr + zi * zi
	movsd	four(%rip), %xmm0 	#  xmm0 = 4.0
	comisd	%xmm1, %xmm0		#  src: xmm1  dest:xmm0
	jbe	.end_while				#  break if xmm0(4) <= xmm1
	cmpl	$254, iteration   	#  src: 254  dest:iteration
	jle	.while_body				#  continue if iteration <= 254
.end_while:
	movl	iteration, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc

four: .double 4.0