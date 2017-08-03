#ifndef PAGING_H
#define PAGING_H

#include <type.h>
#include <cpu/isr.h>

static const int PAGE_SIZE = 1024 * 4;

typedef struct page {
    uint32 present    : 1;
    uint32 rw         : 1;
    uint32 user       : 1;
    uint32 accessed   : 1;
    uint32 dirty      : 1;
    uint32 unused     : 7;
    uint32 frame      : 20;
} page_t;


typedef struct page_table {
    page_t pages[1024];
} page_table_t;

typedef struct page_directory {
    page_table_t *tables[1024];
    uint32 tablesPhysical[1024];
    /*
     * The physical address of tablesPhysical.
     */
    uint32 physicalAddr;
} page_directory_t;

void initialise_paging();

void switch_page_directory(page_directory_t *new);

page_t *get_page(uint32 address, int make, page_directory_t *dir);

void page_fault(registers_t regs);

uint32 *frames;
uint32 nframes;

//extern uint32 placement_address;

#define INDEX_FROM_BIT(a) (a>>5)
#define OFFSET_FROM_BIT(a) (a&31)

static void set_frame(uint32 frame_addr){
    uint32 frame = frame_addr>>12;
    uint32 idx = INDEX_FROM_BIT(frame);
    uint32 off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

static void clear_frame(uint32 frame_addr){
    uint32 frame = frame_addr>>12;
    uint32 idx = INDEX_FROM_BIT(frame);
    uint32 off = OFFSET_FROM_BIT(frame);
    frames[idx] &= (~(0x1 << off));
}

static uint32 first_frame(){
	uint32 i, j;
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
		uint32 idx = first_frame();
		if(idx == (uint32)-1){
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
	uint32 frame;
	if(!(frame=page->frame)){
		return;
	}else{
		clear_frame(frame);
		page->frame = 0x0;
	}
}

#endif
