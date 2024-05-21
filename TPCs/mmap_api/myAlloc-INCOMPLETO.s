.globl allocate # void *allocate( heap *h, unsigned long long int size );
.globl deallocate # void deallocate( void * p );

.equ HEADER_SIZE, 16            #size of space for memory region header
.equ HDR_AVAIL_OFFSET, 0        #Location of the "available" flag in the header
.equ HDR_SIZE_OFFSET, 8         #Location of the size field in the header
.equ UNAVAILABLE, 0             #space that has been given out
.equ AVAILABLE, 1               #space that has been returned

.equ HEAP_BASE_OFFSET, 0        #Location of the heap base address field in the heap descript
.equ HEAP_TOP_OFFSET, 8         #Location of the heap top address field in the heap descriptor
.equ HEAP_LIMIT, 16             #Location of end address in the heap descriptor

.equ NULL,-1

.section .note.GNU-stack,"",@progbits
.text

allocate:
  movq  %rdi, reg1 # reg1 = *h
  movq  %rsi, reg2 # reg2 = bytesToAllocate
  movq  reg1, %rax # %rax = *h
  movq  (%rax), %rax # %rax = h->base
  movq  %rax, reg3 # reg3 = h->base
  jmp .while_loop
.first_if:
  movq  reg3, %rax # %rax = h->base
  movq  (%rax), %rax # %rax = h->base->available
  cmpq  $1, %rax # if (h->base->available == 1)
  jne .second_if # goto .L3
  movq  reg3, %rax # %rax = h->base
  movq  8(%rax), %rax # %rax = h->base->size
  cmpq  %rax, reg2 # if (h->base->size < bytesToAllocate)
  ja  .L3 # goto .L3
  movq  reg3, %rax # %rax = h->base
  movq  $0, (%rax) # h->base->available = 0
  movq  reg3, %rax # %rax = h->base
  addq  $16, %rax # %rax = h->base + 16
  jmp .return # goto .return and return h->base + 16
.second_if:
  movq  reg3, %rax # %rax = h->base
  movq  8(%rax), %rax # %rax = h->base->size 
  addq  $16, %rax # %rax = h->base->size + 16
  addq  %rax, reg3 # reg3 = h->base + h->base->size + 16
.while_loop:
  movq  reg1, %rax # %rax = *h
  movq  8(%rax), %rax # %rax = h->top
  cmpq  %rax, reg3 # if (h->top <= h->base)
  jb  .first_if # goto .L5
  movq  reg1, %rax # %rax = *h
  movq  8(%rax), %rax # %rax = h->top
  cmpq  %rax, reg3 # if (h->top <= h->base)
  jb  .NULL_return_2 # goto .L6
  movq  reg2, %rax # %rax = bytesToAllocate
  addq  $16, %rax # %rax = bytesToAllocate + 16
  movq  %rax, reg4 # reg4 = bytesToAllocate + 16
  movq  reg3, %rdx # %rdx = h->base
  movq  reg4, %rax # %rax = bytesToAllocate + 16
  addq  %rax, %rdx # %rdx = h->base + bytesToAllocate + 16
  movq  reg1, %rax # %rax = *h
  movq  16(%rax), %rax  # %rax = h->limit
  cmpq  %rax, %rdx # if (h->limit < h->base + bytesToAllocate + 16)
  ja  .NULL_return # goto .L7
  movq  reg3, %rax # %rax = h->base
  movq  %rax, reg4  # reg4 = h->base
  movq  reg4, %rax # %rax = h->base
  movq  $0, (%rax) # h->base->available = 0
  movq  reg4, %rax # %rax = h->base
  movq  reg2, %rdx  # %rdx = bytesToAllocate
  movq  %rdx, 8(%rax) # h->base->size = bytesToAllocate
  movq  reg3, %rdx # %rdx = h->base
  movq  reg4, %rax # %rax = h->base
  addq  %rax, %rdx # %rdx = h->base + bytesToAllocate + 16
  movq  reg1, %rax # %rax = *h
  movq  %rdx, 8(%rax) # h->top = h->base + bytesToAllocate + 16
  movq  reg4, %rax # %rax = h->base
  addq  $16, %rax # %rax = h->base + 16
  jmp .return # goto .return and return h->base + 16
.NULL_return:
  movl  $0, %eax # return NULL
  jmp .return # goto .return
.NULL_return_2:
  movl  $0, %eax # return NULL
.return:
  ret

# *p = rdi
deallocate:
    movq    %rdi, %rax          # Store *p in %rbx
    subq    $HEADER_SIZE, %rax  # Move to the header
    movq    $AVAILABLE, (%rax)  # Mark the block as available
    retq                        # Return

# void deallocate(void *address)
# {
#   // Get the block structure address
#   block *blk = (block *)address - 1;
#
#   // Mark the block as available
#   blk->available = 1;
# }