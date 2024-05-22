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