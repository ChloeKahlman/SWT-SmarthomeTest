#include "u8g2_mbed_k66f.h"

uint8_t u8x8_gpio_and_delay_mbed(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
        case U8X8_MSG_GPIO_AND_DELAY_INIT:
            break;
        case U8X8_MSG_DELAY_NANO:
            /* not required for HW SPI */
            break;

        case U8X8_MSG_DELAY_100NANO:
            /* not used at the moment (?) */
            wait_us(1);
            break;

        case U8X8_MSG_DELAY_10MICRO:
            wait_us(arg_int * 10UL);
            break;

        case U8X8_MSG_DELAY_MILLI:
            wait_us(arg_int * 1000UL);
            break;

        case U8X8_MSG_DELAY_I2C:
            /* not required for HW SPI */
            break;

        /* cases for D0 .. D7 and SPI_CLOCK/SPI_DATA skipped, not required for HW SPI */

        case U8X8_MSG_GPIO_I2C_CLOCK:
            /* not required for HW SPI */
            break;
        case U8X8_MSG_GPIO_I2C_DATA:
            /* not required for HW SPI */
            break;
        case U8X8_MSG_GPIO_RESET:
            /* connected to system reset on our system */
            break;

        /* cases for menu skipped */
    default:
        u8x8_SetGPIOResult(u8x8, 1);
        break;
  }
  return 1;
}


extern "C" uint8_t u8x8_byte_k66f_3wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    uint8_t *data;
    static uint8_t last_dc;
    switch(msg) {
        case U8X8_MSG_BYTE_INIT:
            // Send once during the init phase of the display.
//            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);                // disable chipselect
            break;
        case U8X8_MSG_BYTE_SET_DC:
            // Set the level of the data/command pin. arg_int contains the expected output level.
            // Use u8x8_gpio_SetDC(u8x8, arg_int) to send a message to the GPIO procedure.
            //u8x8_gpio_SetDC(u8x8, arg_int);
            last_dc = arg_int;                            // Save D/C state
            break;
        case U8X8_MSG_BYTE_START_TRANSFER:
            // Set the chip select line here.
            // u8x8->display_info->chip_enable_level contains the expected level.
            // Use u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level) to call the GPIO procedure.
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
//            spi.lock();
            oled_cs = 0;
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, NULL);
            break;
        case U8X8_MSG_BYTE_SEND:
            // Send one or more bytes, located at arg_ptr, arg_int contains the number of bytes.
            data = (uint8_t *)arg_ptr;
            while( arg_int > 0 ) {
                // 3-wire mode, so 9-bit transfer: 1 D/C bit, 8 data bits
                if (last_dc == 0) {
                        oled_spi.write( (uint8_t)*data );                  // D/C = 0
                } else {
                        oled_spi.write( 0x100 | (uint8_t)*data );  // D/C = 1
                }
                data++;
                arg_int--;
            }
            break;
        case U8X8_MSG_BYTE_END_TRANSFER:
            // Unselect the device. Use the CS level from here: u8x8->display_info->chip_disable_level
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
//            spi.unlock();              
            oled_cs = 1;
            break;
        default:
            return 0;
    }  
    return 1;
}
