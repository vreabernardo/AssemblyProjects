#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include "myAlloc.h"

heap h;

void debugBlockList(heap *);

void allocate_init(heap *h, unsigned long int memSize);

/**
 * teste alloc/de alloc
 **/
int main(int argc, char *argv[])
{
    unsigned int maxBlock;
    unsigned int heapSpace;

    if (argc != 3)
    {
        printf("%s totalSize maxBlock\n", argv[0]);
        exit(1);
    }
    heapSpace = atoi(argv[1]);
    maxBlock = atoi(argv[2]);

    allocate_init(&h, heapSpace);

    for (int s = 1; s < maxBlock; s *= 2)
    {
        void *ptr = allocate(&h, s);
        if (ptr == NULL)
        {
            printf("No more memory\n");
            return 1;
        }
        deallocate(ptr);
    }
    debugBlockList(&h);

    for (int s = maxBlock; s > 0; s /= 2)
    {
        void *ptr = allocate(&h, s);
        if (ptr == NULL)
        {
            printf("No more memory\n");
            return 1;
        }
    }
    debugBlockList(&h);

    return 0;
}

void debugBlockList(heap *h)
{
    void *p = h->base;
    printf("Available\tSize\n");
    while (p < h->top)
    {
        unsigned long long *pt = p;
        printf("%llu\t%llu\n", *pt, *(pt + 1));
        p = p + 16 + *(pt + 1);
    }
}

unsigned long long int adjustToMultipleOfPageSize(unsigned long int memSize)
{
    unsigned long int pageSize = 4096;
    // printf("About to return %ld\n", (memSize + (pageSize -1)) &  ~(pageSize -1) );
    return (memSize + (pageSize - 1)) & ~(pageSize - 1);
}

void allocate_init(heap *h, unsigned long int memSize)
{
    unsigned long long int realSize = adjustToMultipleOfPageSize(memSize);
    void *addr = mmap(0, realSize, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (addr == (void *)-1)
    {
        perror("allocate_init");
        exit(1);
    }
    h->base = addr;
    h->top = addr;
    h->limit = (void *)((char *)addr + realSize);
}
