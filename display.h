#ifndef DISPLAY_H
#define DISPLAY_H

#include <firmware.h>

#define DISPLAY_CHARS 5

#define CMD_CHAR_OFFSET 2
#define CHAR_H  7
#define CHAR_W  5
#define CHAR_CMD_SIZE  10

void set_pixel(int x, int y, int v);
int read_pixel(int x, int y);
void setup_display();
void update_display();

enum LCD_Command {
    WRITE_CHAR_RAM = 0xD0,
    SET_TEXT       = 0xC0
};

#endif
