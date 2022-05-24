#include "firmware.h"

static volatile uint32_t* _sys_ltime = (uint32_t*)0x02001068;
uint32_t get_sys_ltime() {
    return *_sys_ltime;
}

static volatile uint8_t* _key_state = (uint8_t*)0x0200087f;
uint8_t inline get_key_state() {
    return *_key_state;
}

static volatile uint32_t* reset_ptr = (uint32_t*)0x02100000;
uint8_t reset() {
    return *reset_ptr; // will cause data and reset
}