/*
 * paging.c
 *
 *  Created on: Aug 1, 2017
 *      Author: yan
 */

#include <mem.h>
#include "paging.h"

void initialise_paging(){
	uint32_t mem_end_page = 0x1000000;
	nframes = mem_end_page / 0x1000;
	frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(nframes));
	memset(frames, 0, INDEX_FROM_BIT(nframes));


	page_directory_t *kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	memset(kernel_directory, 0, sizeof(page_directory_t));
	page_directory_t *current_directory = kernel_directory;

	int i = 0;

}
