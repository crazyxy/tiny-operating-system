#ifndef PAGING_H
#define PAGING_H


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
    page_table_t *table[1024];
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

#define INDEX_FROM_BIT(a) (a/32)
#define OFFSET_FROM_BIT(a) (a%32)

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
    frames[idx]
}

#endif
