#include <cpu/isr.h>
#include <string.h>
#include <mem.h>
#include <drivers/screen.h>

void kernel_main(){
    isr_install();
    irq_install();
    asm("int $2");
    asm("int $3");
    kprint("Type something, it will go through the kernel\n"
            "Type END to halt the CPU\n> ");
}
