#include "button.h"
#include "firmware.h"

static const uint8_t       key_count    = 7;
static const enum KeyState key_lst  []  = {KeyPrev, KeyStop, KeyPlay,  KeyNext, KeyPause, KeyVolM, KeyVolP };
static uint32_t            lastClick[]  = {0,       0,       0,        0,       0,        0,       0       };
static const enum Button   key_map  []  = {KeyUp,   KeyLeft, KeyRight, KeyDown, KeyLeft,  KeyLeft, KeyRight};

static uint8_t key_state = 0;

int check_button(enum Button button)
{
  return key_state & button;
}

void update_buttons(void) {
  int btn = (get_key_state() & 0xFE);

  if (btn == KeyMenu)
    reset();

  key_state = 0;

  for (uint8_t b=0; b<key_count; b++){ 
    int pressed = btn == key_lst[b];
    uint32_t t = get_sys_ltime();
    if (pressed && (t - lastClick[b]) > ((key_map[b] == KeyDown) ? CLICK_DELAY_DOWN : CLICK_DELAY)) {
      lastClick[b] = t;
      key_state |= key_map[b];
    }
  }

}