.globl sumPi
.section .note.GNU-stack,"",@progbits
.text

sumPi:         #rdi ni
    movsd zero(%rip), %xmm0
    cvtsi2sdq %rdi, %xmm1
    movsd one(%rip), %xmm2
    divsd %xmm1, %xmm2
    movq $1, %rcx
    
    cycle:
    cmpq %rcx, %rdi
    jb end
    cvtsi2sdq %rcx, %xmm3
    subsd zero_5(%rip), %xmm3
    mulsd %xmm2, %xmm3
    mulsd %xmm3, %xmm3
    movsd one(%rip), %xmm4
    subsd %xmm3, %xmm4
    sqrtsd %xmm4, %xmm4
    addsd %xmm4, %xmm0
    incq %rcx
    jmp cycle

end:
    retq

one:
    .double 1.0
zero:
    .double 0.0
zero_5:
    .double 0.5
four:
    .double 4.0
