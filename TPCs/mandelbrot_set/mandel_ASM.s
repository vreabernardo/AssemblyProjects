.globl computePoint # unsigned char computePoint(double x, double y)

.section .note.GNU-stack,"",@progbits
.text

computePoint:
    
    movq $0, %rdx           # 0 into rdx  
    cvtsi2sdq %rdx, %xmm0   # 0.0 to xmm0 (zi = (double)rdx = 0.0)
    cvtsi2sdq %rdx, %xmm1   # 0.0 to xmm1 (zr = (double)rdx = 0.0)
    movq %rdx, %rcx         # 0 to rcx    (i = rcx = rdx = 0)
    
    cycle:
        # Load max_iterations into RDX
        movq $255, %rdx      
        cmpq %rdx, %rcx            
        jae end              # break if i >= max_iterations (255)

        # Copy zi and zr
        movsd %xmm0, %xmm2   # zi2 = zi
        movsd %xmm1, %xmm3   # zr2 = zr

        # Calculate zi2 = zi^2, zr2 = zr^2
        mulsd %xmm2, %xmm2   # zi2 = zi * zi
        mulsd %xmm3, %xmm3   # zr2 = zr * zr

        # Calculate zi^2 + zr^2
        addsd %xmm2, %xmm4   # zi^2 + zr^2
        addsd %xmm3, %xmm4   # zi^2 + zr^2 = zi^2 + zr^2

        # Load 4.0 into xmm5, since this is a constant, do this outside the loop ideally
        movq $4, %rdx          
        cvtsi2sdq %rdx, %xmm5   # 4.0 to xmm5

        # Compare (zi * zi + zr * zr) with 4.0
        ucomisd %xmm5, %xmm4 
        jae end                # break if zi * zi + zr * zr >= 4.0

        # Increment loop counter
        incq %rcx            
        jmp cycle             # repeat loop
           

end:
    #cvtsd2si %xmm4, %rax   # convert zi to int
    #cvtsd2si %xmm5, %rax   # convert zi to int
    movq %rcx, %rax         
    retq                       
