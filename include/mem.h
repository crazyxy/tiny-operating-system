#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>

void memory_copy(uint8_t*, uint8_t*, int);

uint32_t kmalloc(size_t, int, uint32_t *);

#endif
