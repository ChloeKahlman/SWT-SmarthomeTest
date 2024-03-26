#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "board_freedom.h"

#define KEYPAD_SCAN_RATE_MS     50ms
#define KEYPRESS_BEEP_ENABLED   true
#define KEYPRESS_BEEP_LENGTH_MS 2

#define KEYPAD_KEY_0        '0'
#define KEYPAD_KEY_1        '1'
#define KEYPAD_KEY_2        '2'
#define KEYPAD_KEY_3        '3'
#define KEYPAD_KEY_4        '4'
#define KEYPAD_KEY_5        '5'
#define KEYPAD_KEY_6        '6'
#define KEYPAD_KEY_7        '7'
#define KEYPAD_KEY_8        '8'
#define KEYPAD_KEY_9        '9'
#define KEYPAD_KEY_UP       'A'     // 
#define KEYPAD_KEY_DOWN     'B'     // 
#define KEYPAD_KEY_DEL      'C'     // or DEL: 0x7f
#define KEYPAD_KEY_ENTER    'D'     // or LF:  0x0a
#define KEYPAD_KEY_DOT      '.'     // or '.'
#define KEYPAD_KEY_ESC      'F'     // or ESC: 0x1b

extern bool keypad_keypress;
extern uint8_t keypad_key;

void    keypad_init();
void    keypad_set_scan_flag();
uint8_t keypad_scan();

#endif