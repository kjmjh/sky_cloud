#include <stdio.h>

#define PHYSICAL_MEMORY_SIZE 0x1000000  // 16MB

unsigned char memory[PHYSICAL_MEMORY_SIZE];

typedef struct {
    unsigned long start;
    unsigned long end;
} MemoryRegion;

MemoryRegion memory_regions[10];
int memory_region_count = 0;

void memory_init() {
    memory_regions[0].start = 0;
    memory_regions[0].end = PHYSICAL_MEMORY_SIZE - 1;
    memory_region_count = 1;
}

void *kmalloc(unsigned long size) {
    for (int i = 0; i < memory_region_count; i++) {
        if (memory_regions[i].start + size <= memory_regions[i].end) {
            void *addr = (void *)memory_regions[i].start;
            memory_regions[i].start += size;
            return addr;
        }
    }
    return NULL;
}

void kfree(void *ptr, unsigned long size) {
    // 简单的内存释放
    printf("kfree not implemented\n");
}