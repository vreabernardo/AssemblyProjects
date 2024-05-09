.globl computePoint # unsigned char computePoint(double x, double y)

.section .note.GNU-stack,"",@progbits
.text

# rdi  255
# rcx  i
# xmm0 zi
# xmm1 zr

computePoint:
    movq $255, %rdi # rdi = 255 max iterations
    movq $0, %rax   # rcx = 0 current iteration
    movsd zero(%rip), %xmm0 # xmm0 = 0.0
    movsd zero(%rip), %xmm1 # xmm1 = 0.0    
    
    cycle:
    cmpq %rax, %rdi
    je end     # if rax == rdi, jump to end aka i == 255


    movsd %xmm0, %xmm2 # xmm2 = zi
    movsd %xmm1, %xmm3 # xmm3 = zr
    mulsd %xmm2, %xmm2 # xmm2 = zi^2
    mulsd %xmm3, %xmm3 # xmm3 = zr^2
    addsd %xmm2, %xmm3 # xmm3 = zr^2 + zi^2
    ucomisd four(%rip), %xmm3 # compare xmm3 to 4.0
    jae end # if xmm3 >= 4.0, jump to end
    

    incq %rax
    jmp cycle

end:
    retq

zero:
    .double 0.0
four:
    .double 4.0