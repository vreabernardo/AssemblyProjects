typedef struct
{
  void *base;  // beginning of managed area
  void *top;   // address of last byte allocate
  void *limit; // last address in the area allocated by mmap
} heap;

typedef struct
{
  unsigned long long int available;
  unsigned long long int size;
} block;

#define BLOCK_SIZE sizeof(block)

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

void deallocate(void *p);
