#include "timer.h"
#include "isr.h"
#include "port.h"

#include <function.h>


/*
 * The programmable interval timers is a chip connected to IRQ0.
 */

unsigned int tick = 0;

static void timer_callback(registers_t regs){
    tick ++;
    UNUSED(regs);
}


void init_timer(unsigned int freq){
    register_interrupt_handler(IRQ0, timer_callback);
    unsigned int divisor = TIMER_MAX_FREQ / freq;
    unsigned char l = (unsigned char) (divisor & 0xff);
    unsigned char h = (unsigned char) ((divisor >> 8) & 0xff);
    
    port_byte_out(TIMER_COMMAND, 0x36);
    port_byte_out(TIMER_PORT0, l);
    port_byte_out(TIMER_PORT0, h);
}
