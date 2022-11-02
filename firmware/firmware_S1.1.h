#ifndef FIRMWARE_H
#define FIRMWARE_H

#include <stdint.h>

typedef void func(void);
typedef void func1(uint32_t a);
typedef void func2(uint32_t a, uint32_t b);

// general
static func* reset = (func*)0x3c; // jump to boot


// tron

static func1* tron_ter_task = (func1*)0x75a3d;
static func1* tron_dly_tsk = (func1*)0x0007567d;

// time 
uint32_t get_sys_ltime();

// display
typedef void func_queue_direct_display_cmd(uint8_t* buff, uint32_t len);
static func_queue_direct_display_cmd* queue_direct_display_cmd = (func_queue_direct_display_cmd*)0x3ad21;

// button
uint8_t get_key_state();

enum KeyState {
    KeyPrev   = 0x6c,
    KeyNext   = 0x6e,
    KeyStop   = 0x7a,
    KeyPlay   = 0x74,
    KeyPause  = 0x72,
    KeyVolP   = 0x50,
    KeyVolM   = 0x52,
    KeyRec    = 0x78,
    KeyMenu   = 0x20,
    KeyEndS   = 0x32,
    KeyGroup  = 0x37,
    KeyGroupP = 0x66,
    KeyGroupM = 0x64,

    KeyDevice = 0x1
};

#endif