.globl computePoint # unsigned char computePoint(double x, double y)

.section .note.GNU-stack,"",@progbits
.text

computePoint:
    movsd zero(%rip), %xmm0 # zi = 0.0
    movsd zero(%rip), %xmm1 # zr = 0.0
    movq zero(%rip), %rcx   # iterations = 0
    movq $255, %rdx         # Load max_iterations into RDX

    cycle:
        cmp %rdx, %rcx            
        jge end             # break if i >= max_iterations(255)       
        
        
        
        
        inc %rcx            # i++     
        jmp cycle           # repeat cycle               

end:
    movq %rcx, %rax           
    retq                       


zero: .double 0.0
