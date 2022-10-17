#include "button.h"
#include "firmware.h"

static const enum KeyState key_map[] = { KeyPrev, KeyStop, KeyPlay, KeyNext, KeyPause };
static uint32_t lastClick[] = {0, 0, 0, 0, 0};

int checkButton(enum Button button)
{
  int btn = (get_key_state() & 0xFE);

  if (btn == KeyMenu)
    reset();
  
  int pressed = btn == key_map[button];
  uint32_t t = get_sys_ltime();
  if (pressed == 1 && (t - lastClick[button]) > ((button == KeyDown) ? CLICK_DELAY_DOWN : CLICK_DELAY)) {
    lastClick[button] = t;
    return 1;
  } 

  return 0;
}
