#ifndef IDT_H
#define IDT_H

#include "types.h"

#define KERNEL_CS 0x08


/*
 * Interrupt handler
 */
typedef struct{
    // Lower 16 bits of handler function address
    u16 low_offset;
    // Kernel segment selector
    u16 sel;
    u8 always0;
    /*
     * Bit 7: Interrupt is present
     * Bits 6-5: Previlege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: 
     */
    u8 flags;
    // Higher 16 bits of handler function address
    u16 high_offset;
} __attribute__((packed)) idt_gate_t;


/*
 * A pointer to the array of interrupt handlers.
 */
typedef struct{
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_register_t;


#define IDT_ENTRIES 256

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;


void set_idt_gate(int n, u32 handler);
void set_idt();

#endif
