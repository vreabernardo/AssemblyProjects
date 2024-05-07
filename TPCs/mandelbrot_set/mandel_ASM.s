;----------------------------------------
; Initialization:
;----------------------------------------
; zr = 0.0      
; zi = 0.0      
; iteration = 0 
; max_iterations = 255 
; escape_radius = 4.0  
;----------------------------------------
; while Signature:
;----------------------------------------
; Compute zr*zr + zi*zi
; Test zr*zr + zi*zi < escape_radius
; if false, jumps to END_LOOP
; Test iteration < max_iterations
; if false, jumps to END_LOOP
;----------------------------------------
; while loop body:
;----------------------------------------
; nr = zr*zr - zi*zi + x ; Calculate new real part
; ni = 2*zr*zi + y       ; Calculate new imaginary part
; Update zr and zi with these new values:
; zr = nr
; zi = ni
; Increments iteration
;----------------------------------------
; END_LOOP:
;----------------------------------------
; returns iteration
;----------------------------------------

.globl updateImage  #  void updateImage( buffer, x,     y,  val, base)
.globl computePoint #  unsigned char computePoint( double x, double y)

.section .note.GNU-stack,"",@progbits
.text


updateImage:

    retq




computePoint:        

    retq



                                    
