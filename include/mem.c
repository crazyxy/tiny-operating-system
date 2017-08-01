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
		*p = (unsigned char)c;
		p++;
		len--;
	}
	return s;
}

uint32_t placement_address = 0x10000;
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
   if(align == 1 && (placement_address & (alignment - 1))) {
       placement_address &= -alignment;
       placement_address += alignment;
   }
   if(phy) *phy = placement_address;
   uint32_t ret = placement_address;
   placement_address += size;
   return ret;
}
