#include "timer.h"
#include "isr.h"
#include "port.h"

#include "../libc/function.h"


/*
 * The programmable interval timers is a chip connected to IRQ0.
 */

u32 tick = 0;

static void timer_callback(registers_t regs){
    tick ++;
    UNUSED(regs);
}


void init_timer(u32 freq){
    register_interrupt_handler(IRQ0, timer_callback);
    u32 divisor = TIMER_MAX_FREQ / freq;
    u8 l = (u8) (divisor & 0xff);
    u8 h = (u8) ((divisor >> 8) & 0xff);
    
    port_byte_out(TIMER_COMMAND, 0x36);
    port_byte_out(TIMER_PORT0, l);
    port_byte_out(TIMER_PORT0, h);
}
