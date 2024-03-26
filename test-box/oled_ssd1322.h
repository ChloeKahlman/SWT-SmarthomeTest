#ifndef _OLED_SSD1322_H_
#define _OLED_SSD1322_H_

#include "board_freedom.h"
#include <u8g2.h>
#include "u8g2_mbed_k66f.h"
#include "logos.h"

extern const uint8_t XLargeFont[];
extern const uint8_t LargeFont[];

extern u8g2_t oled;

void oled_init(void);
void oled_splash(void);

#endif /* _OLED_SSD1322_H_ */
