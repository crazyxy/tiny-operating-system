#include <mem.h>
#include <cpu/port.h>
#include "screen.h"

int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);


void screen_backspace(){
    int offset = get_cursor_offset() - 2;
    int col = get_offset_col(offset);
    int row = get_offset_row(offset);
    kprint_at(" ", col, row);
    set_cursor_offset(offset);
}

void kprint_at(char *msg, int col, int row){
    int offset;
    if (col >= 0 && row >= 0){
        offset = get_offset(col, row);
    }else{
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (msg[i] != 0){
        offset = print_char(msg[i++], col, row, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char *msg){
    kprint_at(msg, -1, -1);
}

int print_char(char c, int col, int row, char attr){
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if (col >= MAX_COLS || row >= MAX_ROWS){
        vidmem[2*MAX_COLS*MAX_ROWS-2] = 'E';
        vidmem[2*MAX_COLS*MAX_ROWS-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset = get_offset(col, row);

    if (c == '\n'){
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    }else{
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }


    // Overflow
    if (offset >= MAX_ROWS * MAX_COLS * 2){
        int i;
        for(i = 0; i < MAX_ROWS-1; i ++){
            memory_copy((uint8_t*) VIDEO_ADDRESS + get_offset(0, i),
                    (uint8_t*) VIDEO_ADDRESS + get_offset(0, i+1),
                    MAX_COLS*2);
        }
        char *last_line = (char*) VIDEO_ADDRESS + get_offset(0, MAX_ROWS-1);
        for(i = 0; i < MAX_COLS*2; i ++) last_line[i] = 0;
        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);
    return offset;
}


int get_cursor_offset(){
    port_byte_out(REG_SCREEN_CTRL, 14);
    int pos = port_byte_in(REG_SCREEN_DATA)<<8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    pos += port_byte_in(REG_SCREEN_DATA);
    return pos * 2;
}

void set_cursor_offset(int offset){
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset>>8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset&0xff));
}

void clear_screen(){
    int size = MAX_COLS * MAX_ROWS;
    int i;
    unsigned char *screen = (unsigned char*)VIDEO_ADDRESS;
    for(i = 0; i < size; i ++){
        screen[i<<1] = ' ';
        screen[i<<1|1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}

int get_offset(int col, int row){
    return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset){
    return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset){
    return (offset / 2) % MAX_COLS;
}
