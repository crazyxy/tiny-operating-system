#ifndef MEM_H
#define MEM_H

#include <type.h>
void memory_copy(uint8*, uint8*, int);
uint8* memset(uint8*, int c, uint32);

uint32 kmalloc_a(uint32); 
uint32 kmalloc_p(uint32, uint32 *phy);
uint32 kmalloc_ap(uint32, uint32 *phy);
uint32 kmalloc(uint32);
uint32 kmalloc_int(uint32, int align, uint32 *phy);

#endif
