#include <mem.h>
#include "paging.h"

page_directory_t* kernel_directory, *current_directory;

void initialise_paging(){
	uint32_t mem_end_page = 0x1000000;
	nframes = mem_end_page / 0x1000;
	frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(nframes));
	memset(frames, 0, INDEX_FROM_BIT(nframes));


	kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	memset(kernel_directory, 0, sizeof(page_directory_t));
	current_directory = kernel_directory;

	int i = 0;
    while(i < placement_address){
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
        i += PAGE_SIZE;
    }

    register_interrupt_handler(14, page_fault);

    switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t *dir) {
    current_directory = dir;
    asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(uint32_t address, int make, page_directory_t *dir) {
    address >>= 12;
    unsigned int table_idx = address / 1024;
    if(dir->tables[table_idx]){
        return &dir->tables[table_idx]->pages[address % 1024];
    }else if(make == 1) {
        unsigned int tmp;
        dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
        memset(dir->tables[table_idx], 0, PAGE_SIZE);
        dir->tablesPhysical[table_idx] = tmp | 0x7;
        return &dir->tables[table_idx]->pages[address%1024];
    }else{
        return 0;
    }
}

void page_fault(registers_t regs) {
    uint32_t fault_address;
    asm volatile("mov %%cr2, %0" : "=r" (fault_address));
}
