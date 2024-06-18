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

# void updateImage(unsigned char *buffer, unsigned int x, unsigned int y, unsigned char val, unsigned int base);
updateImage:
    imull	%edx, %r8d          # r8 = y * base
	leal	(%r8,%rsi), %eax    # eax = y * base + x
	movb	%cl, (%rdi,%rax)    # buffer[y * base + x] = v
	retq

# unsigned char computePoint( double x, double y)
computePoint:
    movsd	%xmm0, %xmm15  		# xvalue = x
	movsd	%xmm1, %xmm14   	# yvalue = y
	movl	$0, %eax        	# iteration = 0
	movsd	zero(%rip), %xmm12  # zi = 0
	movsd	zero(%rip), %xmm13  # zr = 0
    jmp while_signature 

	while_body:
	movsd	%xmm13, %xmm0 		# xmm0 = zr
	movapd	%xmm0, %xmm1  		# xmm1 = zr
	mulsd	%xmm0, %xmm1 		# xmm1 = zr * zr
	movsd	%xmm12, %xmm0 		# xmm0 = zi
	movapd	%xmm0, %xmm2 		# xmm2 = zi
	mulsd	%xmm0, %xmm2 		# xmm2 = zi * zi
	subsd	%xmm2, %xmm1 		# xmm1 = zr * zr - zi * zi
	movapd	%xmm1, %xmm0 		# xmm0 = zr * zr - zi * zi
	movsd	%xmm15, %xmm1 		# xmm1 = yvalue
	addsd	%xmm1, %xmm0		# xmm0 = zr * zr - zi * zi + yvalue
	movsd	%xmm0, %xmm3 		# xmm3 = zr * zr - zi * zi + yvalue
	movsd	%xmm13, %xmm0 		# xmm0 = zr
	addsd	%xmm0, %xmm0 		# xmm0 = zr + zr
	mulsd	%xmm12, %xmm0 		# xmm0 = 2 * zr * zi
	movsd	%xmm14, %xmm1 		# xmm1 = xvalue
	addsd	%xmm1, %xmm0 		# xmm0 = 2 * zr * zi + xvalue
	movsd	%xmm0, %xmm4 		# xmm4 = 2 * zr * zi + xvalue
	movsd	%xmm4, %xmm0 		# xmm0 = 2 * zr * zi + xvalue
	movsd	%xmm0, %xmm12 		# zi = 2 * zr * zi + xvalue
	movsd	%xmm3, %xmm0 		# xmm0 = zr * zr - zi * zi + yvalue
	movsd	%xmm0, %xmm13 		# zr = zr * zr - zi * zi + yvalue
	inc		%eax                # iteration++

	while_signature: 
	movsd	%xmm13, %xmm0		#  xmm0 = zr
	movapd	%xmm13, %xmm1		#  xmm1 = zr
	mulsd	%xmm13, %xmm1		#  xmm1 = zr * zr
	movsd	%xmm12, %xmm0		#  xmm0 = zi
	mulsd	%xmm0, %xmm0 		#  xmm0 = zi * zi
	addsd	%xmm0, %xmm1		#  xmm1 = zr * zr + zi * zi
	movsd	four(%rip), %xmm0 	#  xmm0 = 4.0
	comisd	%xmm1, %xmm0		#  src: xmm1  dest:xmm0
	jbe	end_while				#  break if 4 <= xmm1
	cmpl	$255, %eax   	    #  src: 255  dest:iteration
	jne	while_body				#  continue if iteration != 255

	end_while:
	retq					#  return iteration(eax)

four:.double 4.0
zero:.double 0.0


                                    
