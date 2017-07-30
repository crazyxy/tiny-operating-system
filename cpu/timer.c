#include "timer.h"
#include "isr.h"
#include "port.h"

#include <function.h>


/*
 * The programmable interval timers is a chip connected to IRQ0.
 */

uint32_t tick = 0;

static void timer_callback(registers_t regs){
    tick ++;
    UNUSED(regs);
}


void init_timer(uint32_t freq){
    register_interrupt_handler(IRQ0, timer_callback);
    uint32_t divisor = TIMER_MAX_FREQ / freq;
    uint8_t l = (uint8_t) (divisor & 0xff);
    uint8_t h = (uint8_t) ((divisor >> 8) & 0xff);
    
    port_byte_out(TIMER_COMMAND, 0x36);
    port_byte_out(TIMER_PORT0, l);
    port_byte_out(TIMER_PORT0, h);
}
