#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "board_freedom.h"

extern volatile bool buttons_changed;

void button_init();
void button_isr();
bool button_get_state(uint8_t nr);
uint8_t button_get_all();

#endif