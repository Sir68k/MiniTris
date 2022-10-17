#include <display.h>

static const uint8_t setup_cmd[] = {
    0xC0,0x00,0x20,1,2,3,4,5,
    0x20,0x20,0x20,0x20};

// this is the command to send to the display, we keep it also as display buffer
// this means we need to perform a mapping calculation for every pixel set
static uint8_t display_cmd_buffer[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 
};

static uint8_t display_mod_buffer[] = {0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


void set_pixel(int x, int y, int v) {
    int c_char = x / CHAR_W;
    int column = CHAR_W - (x  % CHAR_W);// CHAR_MEM_OFFSET;

    uint8_t* byte_ptr = (uint8_t*)&display_cmd_buffer + CMD_CHAR_OFFSET + (c_char*CHAR_MEM_SIZE) + y;

    *byte_ptr = (*byte_ptr & ~(1 << column)) | (v << column);
}

int read_pixel(int x, int y) {
    if ( x > (CHAR_W * DISPLAY_CHARS - 1) || y > (CHAR_H - 1) || y < 0)
        return 1;

    int c_char = x / CHAR_W;
    int column = CHAR_W - (x % CHAR_W);

    uint8_t* byte_ptr = (uint8_t*)&display_cmd_buffer + CMD_CHAR_OFFSET + (c_char*CHAR_MEM_SIZE) + y;
    
    return (*byte_ptr >> column) & 1;
}


static volatile uint32_t* len_ptr = (uint32_t*)0x02001fe4;
void setup_display() {
    queue_direct_display_cmd((uint8_t*)&setup_cmd, 12);
}

void update_display() {
    for (int i=0; i<DISPLAY_CHARS; i++) {
        display_mod_buffer[1] = 8*i+8;
        for (int x=0; x<8; x++) {
            display_mod_buffer[2+x] = display_cmd_buffer[8*i+x];
        }
        queue_direct_display_cmd((uint8_t*)&display_mod_buffer, 10);
    }

}

void clear_display() {
    
}
