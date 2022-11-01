#ifndef BUTTON_H
#define BUTTON_H

#define CLICK_DELAY 15
#define CLICK_DELAY_DOWN 5

enum Button {
    KeyUp       = 1,
    KeyLeft     = 2,
    KeyRight    = 4,
    KeyDown     = 8
};

int check_button(enum Button button);
void update_buttons(void);
void setup_buttons(void);

#endif