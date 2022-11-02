#include <display.h>
static const uint8_t setup_cmd[] = {SET_TEXT, 0x00, 0x20,0x00,0x01,0x02,0x03,0x04,0x10,0x10,0x10,0x10};

// these are the commands to send to the display, we keep it also as display buffer
// this means we need to perform a mapping calculation for every pixel set
static uint8_t display_cmd_buffer[DISPLAY_CHARS][CHAR_CMD_SIZE] = {
    { WRITE_CHAR_RAM, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { WRITE_CHAR_RAM, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { WRITE_CHAR_RAM, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 
    { WRITE_CHAR_RAM, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { WRITE_CHAR_RAM, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

void set_pixel(int x, int y, int v) {
    if (x<0)
        return;

    uint32_t c_char = (x * 0xCCCD) >> 18; // DIVIDE BY 5
    uint32_t column = CHAR_W - (x - c_char*CHAR_W);

    uint8_t* byte_ptr = (uint8_t*)&display_cmd_buffer[c_char] + CMD_CHAR_OFFSET + y;

    *byte_ptr = (*byte_ptr & ~(1 << column)) | (v << column);
}

int read_pixel(int x, int y) {
    if ( x < 0)
        return 0;
    if ( x > (CHAR_W * DISPLAY_CHARS - 1) || y > (CHAR_H - 1) || y < 0)
        return 1;

    uint32_t c_char = (x * 0xCCCD) >> 18; // DIVIDE BY 5
    uint32_t column = CHAR_W - (x - c_char*CHAR_W);

    uint8_t* byte_ptr = (uint8_t*)&display_cmd_buffer[c_char] + CMD_CHAR_OFFSET + y;
    
    return (*byte_ptr >> column) & 1;
}

void setup_display() {
    queue_direct_display_cmd((uint8_t*)&setup_cmd, 12);
}

void update_display() {
    for (int i=0; i<DISPLAY_CHARS; i++) {
        queue_direct_display_cmd((uint8_t*)&display_cmd_buffer[i], CHAR_CMD_SIZE);
    }
}
