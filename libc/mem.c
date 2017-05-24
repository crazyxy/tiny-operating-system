#include "mem.h"

void memory_copy(char *dst, char *src, int n){
    int i;
    for(i = 0; i < n; i ++){
        *(dst+i) = *(src+i);
    }
}

u32 free_mem_addr = 0x10000;
u32 alignment = 0x1000;
u32 mask = 0xfffff000;

u32 kmalloc(u32 size, int align, u32 *phys_addr){
   if(align == 1 && (free_mem_addr & (alignment-1))){
       free_mem_addr &= mask;
       free_mem_addr += alignment;
   }
   if(phys_addr) *phys_addr = free_mem_addr;
   u32 ret = free_mem_addr;
   free_mem_addr += size;
   return ret;
}
