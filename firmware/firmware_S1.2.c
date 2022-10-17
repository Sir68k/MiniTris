#include "firmware_S1.2.h"

static volatile uint32_t* _sys_ltime = (uint32_t*)0x02000f10;
uint32_t get_sys_ltime() {
    return *_sys_ltime;
}

static volatile uint8_t* _key_state = (uint8_t*)0x0200076b;
uint8_t inline get_key_state() {
    return *_key_state;
}
