#ifndef PAGING_H
#define PAGING_H

#include <cpu/isr.h>

const static int PAGE_SIZE = 1024 * 4;

typedef struct page {
    uint32_t present    : 1;
    uint32_t rw         : 1;
    uint32_t user       : 1;
    uint32_t accessed   : 1;
    uint32_t dirty      : 1;
    uint32_t unused     : 7;
    uint32_t frame      : 20;
} page_t;


typedef struct page_table {
    page_t pages[1024];
} page_table_t;

typedef struct page_directory {
    page_table_t *tables[1024];
    uint32_t tablesPhysical[1024];
    /*
     * The physical address of tablesPhysical.
     */
    uint32_t physicalAddr;
} page_directory_t;

void initialise_paging();

void switch_page_directory(page_directory_t *new);

page_t *get_page(uint32_t address, int make, page_directory_t *dir);

void page_fault(registers_t regs);

uint32_t *frames;
uint32_t nframes;

extern uint32_t placement_address;

#define INDEX_FROM_BIT(a) (a>>5)
#define OFFSET_FROM_BIT(a) (a&31)

static void set_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr>>12;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

static void clear_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr>>12;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] &= (~(0x1 << off));
}

static uint32_t first_frame(){
	uint32_t i, j;
	for(i = 0; i < INDEX_FROM_BIT(nframes); i++){
		if(frames[i] != 0xffffffff){
			for(j = 0; j < 32; j++){
				if(!(frames[i]&(0x1<<j))){
					return i*32+j;
				}
			}
		}
	}
	return -1;
}

void alloc_frame(page_t *page, int is_kernel, int is_writeable){
	if(page->frame){
		return;
	}else{
		uint32_t idx = first_frame();
		if(idx == (uint32_t)-1){
			return;
		}
		set_frame(idx*0x1000);
		page->present = 1;
		page->rw = is_writeable ? 1 : 0;
		page->user = is_kernel ? 0 : 1;
		page->frame = idx;
	}
}


void free_frame(page_t *page){
	uint32_t frame;
	if(!(frame=page->frame)){
		return;
	}else{
		clear_frame(frame);
		page->frame = 0x0;
	}
}

#endif
