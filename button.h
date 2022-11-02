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

enum Button get_current_button(void);

#endif