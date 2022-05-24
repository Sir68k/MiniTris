#include "firmware.h"
#include "display.h"
#include "tetris.h"
#include "button.h"

void main() {
    // kill all the tasks that we don't need
    for (int i=0; i<8; i++)
        tron_ter_task(i);

    queue_direct_display_cmd("\xc0\x00Tetris",8);

    while (checkButton(KeyUp) == 0) {
        update_display();
        tron_dly_tsk(10);
    }

    setup_display();
    playTetris();    
}
