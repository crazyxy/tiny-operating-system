#include <mem.h>

void memory_copy(uint8_t *dst, uint8_t *src, int n){
    int i;
    for(i = 0; i < n; i ++){
        *(dst+i) = *(src+i);
    }
}

static uint32_t free_mem_addr = 0x10000;
static uint32_t alignment = 0x1000;
static uint32_t mask = 0xfffff000;

uint32_t kmalloc(size_t size, int align, uint32_t *phys_addr){
   if(align == 1 && (free_mem_addr & (alignment-1))){
       free_mem_addr &= mask;
       free_mem_addr += alignment;
   }
   if(phys_addr) *phys_addr = free_mem_addr;
   uint32_t ret = free_mem_addr;
   free_mem_addr += size;
   return ret;
}
