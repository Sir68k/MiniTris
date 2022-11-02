#include "firmware.h"
#include "display.h"
#include "tetris.h"
#include "button.h"

void main() {
    // kill all the tasks that we don't need
    for (int i=0; i<9; i++)
        tron_ter_task(i+1);

    queue_direct_display_cmd("\xc0\x00Tetris",8);

    enum Button button = 0;    
    while (button != KeyUp) {
        update_display();
        tron_dly_tsk(10);
        button = get_current_button();
    }

    setup_display();
    playTetris();    
}