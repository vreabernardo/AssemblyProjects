.globl computePoint # unsigned char computePoint(double x, double y)

.section .note.GNU-stack,"",@progbits
.text

computePoint:
    movsd zero(%rip), %xmm0 # zi = 0.0
    movsd zero(%rip), %xmm1 # zr = 0.0
    movq  zero(%rip), %rcx   # iterations = 0
    movq $255, %rdx         # Load max_iterations into RDX
    movsd four(%rip), %xmm5 # Load 4.0 into XMM5


    cycle:
        cmp %rdx, %rcx            
        jge end              # break if i >= max_iterations(255)
        movsd %xmm0, %xmm2   # zi2 = zi
        movsd %xmm1, %xmm3   # zr2 = zr
        mulsd %xmm0, %xmm2   # zi2 = zi * zi
        mulsd %xmm1, %xmm3   # zr2 = zr * zr
        movsd %xmm2, %xmm4   # zi3 = zi2
        addsd %xmm3, %xmm4   # zi3 = zi * zi + zr * zr
        ucomisd %xmm4, %xmm5 # compare (zi * zi + zr * zr) with 4.0
        jge end              # break if zi * zi + zr * zr >= 4.0
        
        
        
        
        
        inc %rcx            # i++     
        jmp cycle           # repeat cycle               

end:
    movq %rcx, %rax           
    retq                       


zero: .double 0.0
four: .double 4.0
