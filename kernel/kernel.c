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

void user_input(char *input){
    if(strcmp(input, "END") == 0){
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }else if(strcmp(input, "PAGE") == 0){
        uint32_t phys_addr;
        uint32_t page = kmalloc_ap(1000, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    }
    kprint(input);
    kprint("\n> ");
}
