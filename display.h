#ifndef DISPLAY_H
#define DISPLAY_H

#include <firmware.h>

#define DISPLAY_CHARS 5

#define CMD_CHAR_OFFSET 4
#define CHAR_H  7
#define CHAR_W  5
#define CHAR_MEM_OFFSET 1
#define CHAR_MEM_SIZE  8

#define CMD_LENGTH (CMD_CHAR_OFFSET + CHAR_MEM_SIZE * DISPLAY_CHARS)

void set_pixel(int x, int y, int v);
int read_pixel(int x, int y);
void setup_display();
void update_display();
void clear_display();

#endif
