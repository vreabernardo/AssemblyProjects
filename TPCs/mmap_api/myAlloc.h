#include <stddef.h> // Include for NULL
#include <stdint.h> // Include for standard integer types

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

void *allocate(heap *h, unsigned long long int bytesToAllocate)
{
  // Initialize a pointer to iterate through the blocks
  block *currentBlock = (block *)h->base;

  // Iterate through the blocks until finding a suitable block or reaching the top
  while ((void *)currentBlock < h->top)
  {
    // Check if the block is available and has sufficient size
    if (currentBlock->available == 1 && currentBlock->size >= bytesToAllocate)
    {
      // Mark the block as unavailable
      currentBlock->available = 0;
      // Return the address of the block + sizeof(block)
      return (void *)currentBlock + sizeof(block);
    }
    // Move to the next block
    currentBlock = (block *)((void *)currentBlock + sizeof(block) + currentBlock->size);
  }

  // If it reached the top, try to create a new block
  if ((void *)currentBlock >= h->top)
  {
    // Calculate the required size for the new block
    unsigned long long int blockSize = bytesToAllocate + sizeof(block);
    // Check if there is enough space for the new block
    if ((void *)currentBlock + blockSize <= h->limit)
    {
      // Mark the new block as available
      block *newBlock = (block *)currentBlock;
      newBlock->available = 0;
      newBlock->size = bytesToAllocate;
      // Update the top of the heap
      h->top = (void *)currentBlock + blockSize;
      // Return the address of the new block + sizeof(block)
      return (void *)newBlock + sizeof(block);
    }
    else
    {
      // There is not enough space for the new block
      return NULL;
    }
  }

  // Did not find a suitable block and did not reach the top
  return NULL;
}

// Function to deallocate memory
void deallocate(void *address)
{
  // Get the block structure address
  block *blk = (block *)address - 1;

  // Mark the block as available
  blk->available = 1;
}
