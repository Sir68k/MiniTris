#include "button.h"
#include "firmware.h"

static const uint8_t       key_count    = 7;
static uint32_t            lastClick    = 0;
static const enum KeyState key_lst  []  = {KeyPrev, KeyStop, KeyPlay,  KeyNext, KeyPause, KeyVolM, KeyVolP };
static const enum Button   key_map  []  = {KeyUp,   KeyLeft, KeyRight, KeyDown, KeyLeft,  KeyLeft, KeyRight};

enum Button get_current_button(void) {
  int btn = (get_key_state() & 0xFE);

  if (btn == KeyMenu)
    reset();

  for (uint8_t b=0; b<key_count; b++){ 
    int pressed = btn == key_lst[b];
    uint32_t t = get_sys_ltime();

    if (pressed && (t - lastClick) > ((key_map[b] == KeyDown) ? CLICK_DELAY_DOWN : CLICK_DELAY)) {
      lastClick = t;
      return key_map[b];
    }
  }

  return 0;
}