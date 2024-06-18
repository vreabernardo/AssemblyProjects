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

#define BLOCK_SIZE 16

void *allocate(heap *h, unsigned long long int bytesToAllocate);
void deallocate(void *p);
