#include <mem.h>

uint32 placement_address = 0x10000;
uint32 alignment = 0x1000;

void memory_copy(uint8 *dst, uint8 *src, int n){
    int i;
    for(i = 0; i < n; i ++){
        *(dst+i) = *(src+i);
    }
}

uint8 *memset(uint8 *s, int c, uint32 len){
	uint8 *p = s;
	while(len > 0){
		*p = (uint8) c;
		p++;
		len--;
	}
	return s;
}


uint32 kmalloc_a(uint32 size) {
    return kmalloc_int(size, 1, 0);
}

uint32 kmalloc_p(uint32 size, uint32 *phy) {
    return kmalloc_int(size, 0, phy);
}

uint32 kmalloc_ap(uint32 size, uint32 *phy) {
    return kmalloc_int(size, 1, phy);
}

uint32 kmalloc(uint32 size) {
    return kmalloc_int(size, 0, 0);
}

uint32 kmalloc_int(uint32 size, int align, uint32 *phy) {
   if(align == 1 && (placement_address & (alignment - 1))) {
       placement_address &= -alignment;
       placement_address += alignment;
   }
   if(phy) *phy = placement_address;
   uint32 ret = placement_address;
   placement_address += size;
   return ret;
}
