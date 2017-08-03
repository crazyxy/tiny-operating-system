#include <type.h>
#include <mem.h>
#include <cpu/port.h>
#include <cpu/isr.h>
#include <string.h>
#include <function.h>
#include <kernel/kernel.h>
#include "keyboard.h"
#include "screen.h"

static char key_buffer[256];

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs){
    uint8 scancode = port_byte_in(KEYBOARD_DATA);
    
    if(scancode > SC_MAX) return;

    if(scancode == BACKSPACE){
        backspace(key_buffer);
        screen_backspace();
    }else if(scancode == ENTER){
        kprint("\n");
        user_input(key_buffer);
        key_buffer[0] = '\0';
    }else{
        char letter = sc_ascii[(int)scancode];
        char str[] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }

    UNUSED(regs);
}

void user_input(char *input){
    if(strcmp(input, "END") == 0){
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }else if(strcmp(input, "PAGE") == 0){
        uint32 phys_addr;
        uint32 page = kmalloc_ap(1000, &phys_addr);
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

void init_keyboard(){
    // IRQ1 is reserved for keyboard
    register_interrupt_handler(IRQ1, keyboard_callback);
}
