#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../drivers/screen.h"

void main(){
    isr_install();
    irq_install();
    clear_screen();
    kprint("Type something, it will go through the kernel\n"
            "Type END to halt the CPU\n> ");
}

void user_input(char *input){
    if(strcmp(input, "END") == 0){
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    kprint(input);
    kprint("\n> ");
}
