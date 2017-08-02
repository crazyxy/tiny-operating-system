#ifndef MEM_H
#define MEM_H

#include <stdint.h>


static uint32_t placement_address = 0x10000;
static uint32_t alignment = 0x1000;

void memory_copy(uint8_t*, uint8_t*, int);
void* memset(void*, int c, unsigned int);

uint32_t kmalloc_a(uint32_t); 
uint32_t kmalloc_p(uint32_t, uint32_t *phy);
uint32_t kmalloc_ap(uint32_t, uint32_t *phy);
uint32_t kmalloc(uint32_t);
uint32_t kmalloc_int(uint32_t, int align, uint32_t *phy);

#endif
