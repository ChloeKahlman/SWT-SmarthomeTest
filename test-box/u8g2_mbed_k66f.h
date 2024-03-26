#ifndef _U8G2_MBED_H_
#define _U8G2_MBED_H_

#include "board_freedom.h"
#include <u8g2.h>

uint8_t u8x8_gpio_and_delay_mbed(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern "C" uint8_t u8x8_byte_k66f_3wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#endif