.globl updateImage  #  void updateImage( buffer, x,     y,  val, base)
.globl computePoint #  unsigned char computePoint( double x, double y)

.section .note.GNU-stack,"",@progbits
.text


# Arguments:
# %rdi = buffer (base address)
# %rsi = x
# %edx = y
# %cl = v (0-255)
# %r8 = base (width of the buffer)

updateImage:
    imull	%edx, %r8d       # r8 = y * base
	leal	(%r8,%rsi), %eax # eax = y * base + x
	movb	%cl, (%rdi,%rax) # buffer[y * base + x] = v
	retq

computePoint:
    # load 0 to xmm14, xmm15, eax 
    pxor	%xmm14, %xmm14
    pxor	%xmm15, %xmm15
    xor     %eax, %eax
    pxor	%xmm12, %xmm12 
    pxor	%xmm13, %xmm13      

    # load x and y to xmm14 and xmm15
    movsd	%xmm0, %xmm15   # xvalue = x
	movsd	%xmm1, %xmm14   # yvalue = y
	# load iterations to eax
    movl	$0, %eax        # iteration = 0

    # zi = 0
	pxor	%xmm0, %xmm0    # xmm0 = 0
	movsd	%xmm0, %xmm12   # zi = xmm0 = 0

    # zr = 0
	pxor	%xmm0, %xmm0    # xmm0 = 0
	movsd	%xmm0, %xmm13   # zr = xmm0 = 0
    
    jmp while_signature 

# TODO: comment this rotine
while_body:
	movsd	%xmm13, %xmm0
	movapd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	movsd	%xmm12, %xmm0
	movapd	%xmm0, %xmm2
	mulsd	%xmm0, %xmm2
	subsd	%xmm2, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm15, %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, %xmm3
	movsd	%xmm13, %xmm0
	addsd	%xmm0, %xmm0
	mulsd	%xmm12, %xmm0
	movsd	%xmm14, %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, %xmm4
	movsd	%xmm4, %xmm0
	movsd	%xmm0, %xmm12
	movsd	%xmm3, %xmm0
	movsd	%xmm0, %xmm13
	addl	$1, %eax

while_signature: 
    movsd	%xmm13, %xmm0		#  xmm0 = zr
	movapd	%xmm0, %xmm1		#  xmm1 = zr
	mulsd	%xmm0, %xmm1		#  xmm1 = zr * zr
	movsd	%xmm12, %xmm0		#  xmm0 = zi
	mulsd	%xmm0, %xmm0 		#  xmm0 = zi * zi
	addsd	%xmm0, %xmm1		#  xmm1 = zr * zr + zi * zi
	movsd	four(%rip), %xmm0 	#  xmm0 = 4.0
	comisd	%xmm1, %xmm0		#  src: xmm1  dest:xmm0
	jbe	end_while				#  break if xmm0(4) <= xmm1
	cmpl	$254, %eax   	    #  src: 254  dest:iteration
	jle	while_body				#  continue if iteration <= 254

end_while:
    retq

four:.double 4.0


                                    
