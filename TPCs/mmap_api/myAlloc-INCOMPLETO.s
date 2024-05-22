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
  # Save the function arguments: h (heap pointer) and bytesToAllocate
  movq  %rdi, %r8            # %r8 = h
  movq  %rsi, %r9            # %r9 = bytesToAllocate

  # Initialize currentBlock to h->base
  movq  %r8, %rax
  movq  (%rax), %rax         # %rax = h->base
  movq  %rax, %r10           # %r10 = currentBlock
  jmp check_loop_condition   # Jump to the loop condition check

find_suitable_block:
  # Inside the loop: check if the current block is available
  movq  %r10, %rax
  movq  (%rax), %rax         # %rax = currentBlock->available
  testq %rax, %rax           # Test if currentBlock->available is zero
  je  check_block_size       # If available, jump to size check

  # Check if the block size is sufficient
  movq  %r10, %rax
  movq  8(%rax), %rax        # %rax = currentBlock->size
  cmpq  %rax, %r9            # Compare currentBlock->size with bytesToAllocate
  ja  check_block_size       # If currentBlock->size >= bytesToAllocate, jump to allocate

  # Mark the block as unavailable
  movq  %r10, %rax
  movq  $0, (%rax)           # currentBlock->available = 0

  # Return the address of the block + BLOCK_SIZE
  movq  %r10, %rax
  addq  $16, %rax            # %rax = currentBlock + BLOCK_SIZE
  jmp return_pointer         # Return the pointer

check_block_size:
  # Move to the next block
  movq  %r10, %rax
  movq  8(%rax), %rax        # %rax = currentBlock->size
  addq  $16, %rax            # %rax = currentBlock->size + BLOCK_SIZE
  addq  %rax, %r10           # currentBlock = currentBlock + currentBlock->size + BLOCK_SIZE

check_loop_condition:
  # Loop condition: check if currentBlock < h->top
  movq  %r8, %rax
  movq  8(%rax), %rax        # %rax = h->top
  cmpq  %rax, %r10           # Compare h->top with currentBlock
  jb  find_suitable_block    # If currentBlock < h->top, repeat the loop

  # If we reached here, no suitable block was found, so try to create a new one

  # Calculate the required block size
  movq  %r9, %rax
  addq  $16, %rax            # blockSize = bytesToAllocate + BLOCK_SIZE
  movq  %rax, %r11           # %r11 = blockSize

  # Check if there's enough space for a new block
  movq  %r10, %rdx
  movq  %r11, %rax
  addq  %rax, %rdx           # newBlockEnd = currentBlock + blockSize
  movq  %r8, %rax
  movq  16(%rax), %rax       # %rax = h->limit
  cmpq  %rax, %rdx           # Compare newBlockEnd with h->limit
  ja  allocation_fail        # If newBlockEnd > h->limit, allocation fails

create_new_block:
  # Create and initialize the new block
  movq  %r10, %rax
  movq  $0, (%rax)           # currentBlock->available = 0
  movq  %r10, %rax
  movq  %r9, %rdx
  movq  %rdx, 8(%rax)        # currentBlock->size = bytesToAllocate

  # Update the top of the heap
  movq  %r10, %rdx
  movq  %r11, %rax
  addq  %rax, %rdx           # newTop = currentBlock + blockSize
  movq  %r8, %rax
  movq  %rdx, 8(%rax)        # h->top = newTop

  # Return the address of the new block + BLOCK_SIZE
  movq  %r10, %rax
  addq  $16, %rax            # %rax = currentBlock + BLOCK_SIZE
  jmp return_pointer         # Return the pointer

allocation_fail:
  # Allocation fails
  movl  $0, %eax             # Return 0

return_pointer:
  ret                        # Return

# *p = rdi
deallocate:
    subq    $HEADER_SIZE, %rdi  # Move to the available flag in the header
    movq    $AVAILABLE, (%rdi)  # Mark the block as available
    retq                        # Return

# void deallocate(void *address)
# {
#   // Get the block structure address
#   block *blk = (block *)address - 1;
#
#   // Mark the block as available
#   blk->available = 1;
# } 