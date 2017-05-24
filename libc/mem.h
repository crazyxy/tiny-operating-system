#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void memory_copy(char*, char*, int);

u32 kmalloc(u32, int, u32 *);

#endif
