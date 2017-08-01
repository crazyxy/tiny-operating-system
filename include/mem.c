#include <mem.h>

void memory_copy(uint8_t *dst, uint8_t *src, int n){
    int i;
    for(i = 0; i < n; i ++){
        *(dst+i) = *(src+i);
    }
}

void* memset(void *s, int c, unsigned int len){
	unsigned char *p = s;
	while(len > 0){
		*p = (unsigned char)s;
		p++;
		len--;
	}
	return s;
}

static uint32_t free_mem_addr = 0x10000;
static uint32_t alignment = 0x1000;

uint32_t kmalloc_a(uint32_t size) {
    return kmalloc_int(size, 1, 0);
}

uint32_t kmalloc_p(uint32_t size, uint32_t *phy) {
    return kmalloc_int(size, 0, phy);
}

uint32_t kmalloc_ap(uint32_t size, uint32_t *phy) {
    return kmalloc_int(size, 1, phy);
}

uint32_t kmalloc(uint32_t size) {
    return kmalloc_int(size, 0, 0);
}


uint32_t kmalloc_int(uint32_t size, int align, uint32_t *phy) {
   if(align == 1 && (free_mem_addr & (alignment - 1))) {
       free_mem_addr &= -alignment;
       free_mem_addr += alignment;
   }
   if(phy) *phy = free_mem_addr;
   uint32_t ret = free_mem_addr;
   free_mem_addr += size;
   return ret;
}
