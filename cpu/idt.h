#ifndef IDT_H
#define IDT_H

#include <stdint.h>


#define low_16(address) (uint16_t)((address)&0xffff)
#define high_16(address) (uint16_t)(((address)>>16)&0xffff)

#define KERNEL_CS 0x08


/*
 * Interrupt handler
 */
typedef struct{
    // Lower 16 bits of handler function address
    uint16_t low_offset;
    // Kernel segment selector
    uint16_t sel;
    uint8_t always0;
    /*
     * Bit 7: Interrupt is present
     * Bits 6-5: Previlege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: 
     */
    uint8_t flags;
    // Higher 16 bits of handler function address
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;


/*
 * A pointer to the array of interrupt handlers.
 */
typedef struct{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;


#define IDT_ENTRIES 256

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;


void set_idt_gate(int n, uint32_t handler);
void set_idt();

#endif
