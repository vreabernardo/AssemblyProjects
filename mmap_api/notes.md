### TODO:
- [ ] allocate
- [x] deallocate

## allocate(heap *h, unsigned long long int bytesToAllocate)

This function returns the address of a block with a size greater than or equal to `bytesToAllocate`. 
Starting from `h->base`, it jumps to the next block structure. 
The loop terminates when one of the following conditions is met:

1. A block structure `b` is found that satisfies the condition `(b->available == 1) && (b->size >= bytesToAllocate)`. 
    In this case, it returns the address `b + sizeof(block)` to the user and sets `b->available` to 0.

2. The value of `h->top` is exceeded. 
    In this case, a new block with size `bytesToAllocate` should be created. 
    If successful, the procedure is the same as in 1; the `h` structure should be updated. 
    If it's not possible to create the new block because it would exceed the `h->limit` address, the function should do nothing and return -1.

``` c
#define BLOCK_SIZE 16

void *allocate(heap *h, unsigned long long int bytesToAllocate)
{
  // Initialize a pointer to iterate through the blocks
  block *currentBlock = (block *)h->base;

  // Iterate through the blocks until finding a suitable block or reaching the top
  while ((void *)currentBlock < h->top)
  {
    // Check if the block is available and has sufficient size
    if (currentBlock->available && currentBlock->size >= bytesToAllocate)
    {
      // Mark the block as unavailable
      currentBlock->available = 0;
      // Return the address of the block + sizeof(block)
      return (void *)currentBlock + BLOCK_SIZE;
    }
    // Move to the next block
    currentBlock = (block *)((void *)currentBlock + BLOCK_SIZE + currentBlock->size);
  }

  // If reached the top, try to create a new block
  unsigned long long int blockSize = bytesToAllocate + BLOCK_SIZE;
  if ((void *)currentBlock + blockSize <= h->limit)
  {
    // Create and initialize the new block
    currentBlock->available = 0;
    currentBlock->size = bytesToAllocate;
    // Update the top of the heap
    h->top = (void *)currentBlock + blockSize;
    // Return the address of the new block + sizeof(block)
    return (void *)currentBlock + BLOCK_SIZE;
  }

  // Not enough space for a new block
  return 0;
}
``` 

## deallocate(void *address)

The function sets the `available` field of the block structure to 1 (is Available).

``` c
void deallocate(void *address)
{
  // Get the block structure address
  block *blk = (block *)address - 1;

  // Mark the block as available
  blk->available = 1;
}
``` 