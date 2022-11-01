#include "firmware.h"
#include "display.h"
#include "tetris.h"
#include "button.h"

void __attribute__((target("arm"))) main() {
    // kill all the tasks that we don't need
    for (int i=0; i<9; i++)
        tron_ter_task(i+1);

    queue_direct_display_cmd("\xc0\x00Tetris",8);

    //tron_dly_tsk(10);
    while (check_button(KeyUp) == 0) {
        update_display();
        tron_dly_tsk(10);
        update_buttons();
    }
    //reset();

    setup_display();
    //tron_dly_tsk(10);
    playTetris();    
}
