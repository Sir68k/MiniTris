#include <display.h>

static const uint8_t setup_cmd[] = {0x0F,0x2C,0xC0,0x00,0x20,0,1,2,3,4};

// this is the command to send to the display, we keep it also as display buffer
// this means we need to perform a mapping calculation for every pixel set
static uint8_t display_cmd_buffer[] = {
    0xF, 0x2c, 0xD0, 0x00,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 
};

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

void setup_display() {
    queue_direct_display_cmd((uint8_t*)&setup_cmd, 10);
    //tron_dly_tsk(10);
}

void update_display() {
    queue_direct_display_cmd((uint8_t*)&display_cmd_buffer, CMD_LENGTH);
}

void clear_display() {
    
}
