#ifndef _BOARD_FREEDOM_H_
#define _BOARD_FREEDOM_H_

#include <mbed.h>
#include <MCP23017.h>
#include "mcp4728.h"
#include "oled_ssd1322.h"
#include "keypad.h"
#include "buttons.h"
#include "adc.h"

#define oled_spi spi0

#define i2c1 i2c

extern uint32_t millis;

#define SYSTEM_VREF_VOLTAGE_DEFAULT     (float)(3.0)
extern float system_vref_voltage;

extern SPI spi0;
extern SPI spi1;
extern I2C i2c;
extern I2C i2c0;
extern MCP23017 mcp;

extern DigitalOut led_board_red;
extern DigitalOut led_board_green;
extern DigitalOut led_board_blue;
extern DigitalOut led_fp_sw;
extern DigitalOut led_fp_red;
extern DigitalOut led_fp_green;
extern DigitalOut buzz;

extern DigitalIn button_0;
extern DigitalIn button_1;
extern DigitalIn button_2;
extern DigitalIn button_3;

extern DigitalOut dout0;
extern DigitalOut dout1;
extern DigitalOut dout2;
extern DigitalOut dout3;
extern DigitalOut dout4;
extern DigitalOut dout5;
extern DigitalOut dout6;

extern DigitalIn  din0;
extern DigitalIn  din1;
extern DigitalIn  din2;
extern DigitalIn  din3;
extern DigitalIn  din4;
extern DigitalIn  din5;
extern DigitalIn  din6;

extern PwmOut     pwm0;
extern PwmOut     pwm1;
extern PwmOut     pwm2;
extern PwmOut     pwm3;



// FIXME: Something is wrong with these pin 'numbers'
extern AnalogIn ain0;
extern AnalogIn ain1;
extern AnalogIn ain2;
extern AnalogIn ain3;

extern DigitalOut  oled_cs;
extern DigitalOut  i2c_buff_nen;    // /EN pin on the TCA9406 I2C buffer (inverted: 0=enable, 1=disable)
extern InterruptIn mcp_int_a;
extern InterruptIn mcp_int_b;


// LEDs on FRDM-K66F board
extern DigitalOut BOARD_LED_RED;
extern DigitalOut BOARD_LED_GREEN;
extern DigitalOut BOARD_LED_BLUE;



// MCP23017 GPIO expander on front panel (note MBED uses 8-bit I2C addresses)
#define MCP23017_FRONT_ADDRESS  (0x27<<1)
// MCP23017 GPIO pins;    dir: 0=out, 1=in;    var: 0=low, 1=high;    pull: 0=disabled, 1=enabled;    pol: 0=normal, 1=inverted;    int: 0=disabled, 1=enabled
//                          pin          dir  var  pull pol  int     mcp_pin_name 
#define MCP_KP_ROW_A         0      //    1    x    0    1    0      GPA0           // x = val doesn't care 'cause it's an input 
#define MCP_KP_ROW_B         1      //    1    x    0    1    0      GPA1
#define MCP_KP_COL_1         2      //    0    0    0    0    0      GPA2
#define MCP_KP_COL_2         3      //    0    0    0    0    0      GPA3
#define MCP_KP_COL_3         4      //    0    0    1    0    0      GPA4
#define MCP_KP_COL_4         5      //    0    0    1    0    0      GPA5
#define MCP_KP_ROW_D         6      //    1    x    1    1    0      GPA6
#define MCP_KP_ROW_C         7      //    1    x    1    1    0      GPA7
#define MCP_BTN0_PIN         8      //    1    x    1    1    1      GPB0
#define MCP_BTN1_PIN         9      //    1    x    1    1    1      GPB1
#define MCP_BTN2_PIN        10      //    1    x    1    1    1      GPB2
#define MCP_BTN3_PIN        11      //    1    x    1    1    1      GPB3
#define MCP_LED_BLUE_PIN    12      //    0    0    0    0    0      GPB4
#define MCP_SPARE1_PIN      13      //    1    x    1    0    0      GPB5
#define MCP_SPARE2_PIN      14      //    1    x    1    0    0      GPB6
#define MCP_SPARE3_PIN      15      //    1    x    1    0    0      GPB7

#define MCP_GPA_DIR     0b11000011
#define MCP_GPA_VAL     0b00000000
#define MCP_GPA_PULL    0b11000011
#define MCP_GPA_POL     0b11000011
#define MCP_GPA_INT     0b11000011

#define MCP_GPB_DIR     0b11101111
#define MCP_GPB_VAL     0b00000000
#define MCP_GPB_PULL    0b11101111
#define MCP_GPB_POL     0b00001111
#define MCP_GPB_INT     0b00001111

void board_init();
void dout_write(uint8_t db);
uint8_t din_read();
void system_set_vref_voltage(float vref);

#endif
