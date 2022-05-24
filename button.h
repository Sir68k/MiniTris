#ifndef BUTTON_H
#define BUTTON_H

#define CLICK_DELAY 15
#define CLICK_DELAY_DOWN 5

enum Button {
    KeyUp    = 0,
    KeyLeft  = 1,
    KeyRight = 2,
    KeyDown  = 3
};

int checkButton(enum Button button);
void setupButtons(void);

#endif