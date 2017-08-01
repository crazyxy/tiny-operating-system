#ifndef TIMER_H
#define TIMER_H

#define TIMER_MAX_FREQ 1193182
#define TIMER_PORT0 0x40
#define TIMER_PORT1 0x41
#define TIMER_PORT2 0x42
#define TIMER_COMMAND 0x43

void init_timer(unsigned int freq);

#endif
