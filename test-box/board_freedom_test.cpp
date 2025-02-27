#include "board_freedom.h"
#include "board_freedom_test.h"
#include "buttons.h"
#include "keypad.h"
#include "u8g2.h"
#include "adc.h"
#include "oled_ssd1322.h"

Ticker blinky_switch;

static void pwm_test_fade(PwmOut* pwm);

void blinkenlights()
{
    printf("# blinkenlights()\n");
    buzz = 1;
    led_fp_sw = 1;
    led_fp_red = 1;
    mcp.digitalWrite(MCP_LED_BLUE_PIN, 0);
    ThisThread::sleep_for(500ms);
    led_fp_red = 0;
    led_fp_green = 1;
    mcp.digitalWrite(MCP_LED_BLUE_PIN, 0);
    ThisThread::sleep_for(500ms);
    led_fp_red = 0;
    led_fp_green = 0;
    mcp.digitalWrite(MCP_LED_BLUE_PIN, 1);
    ThisThread::sleep_for(500ms);
    buzz = 0;
    led_fp_sw = 0;
    led_fp_red = 0;
    led_fp_green = 0;
    mcp.digitalWrite(MCP_LED_BLUE_PIN, 0);
}


void task_blinky_switch_init()
{
    blinky_switch.attach(&task_blinky_switch, 500ms);
}


 void task_blinky_switch()
 {
     led_fp_sw = !led_fp_sw;
 }


void keypad_test()
{
    if (keypad_has_key()) {
        printf("keypress: '%c'\n", keypad_get_char());
        keypad_clear_keys();
    }
}


void keypad_test_oled()
{
    const  int xhome = 80;  // Initial positions
    const  int yhome = 7 + 1 + u8g2_GetMaxCharHeight(&oled);         // Initial positions
    static int x = xhome;
    static int y = yhome;
    char buf[2] = {0x00, 0x00};

    if (keypad_has_key()) {
        buf[0] = keypad_get_char();
        printf("# keypad_test_oled(): keypress '%c' cur_xy=%i,%i    ", buf[0], x, y);

        switch (buf[0]) {
            case '0' ... '9':
            case '.':
                //printf("DIGIT pressed\n");
                u8g2_SetDrawColor(&oled, 0);
                u8g2_DrawBox(&oled, x, y-u8g2_GetMaxCharHeight(&oled), u8g2_GetMaxCharWidth(&oled), u8g2_GetMaxCharHeight(&oled));
                u8g2_SetDrawColor(&oled, 1);
                u8g2_DrawUTF8(&oled, x, y, buf);
                u8g2_SendBuffer(&oled);
                x += u8g2_GetMaxCharWidth(&oled) + 1;
                break;
            case '\e':
                //printf("ESC pressed\n");
                x = xhome;
                y = yhome;
                u8g2_SetDrawColor(&oled, 0);
	            u8g2_DrawBox(&oled, xhome, 0, u8g2_GetDisplayWidth(&oled) - xhome, u8g2_GetDisplayHeight(&oled)-1);
	            u8g2_SetDrawColor(&oled, 1);
	            u8g2_SendBuffer(&oled);
                break;
            case '\n':
                //printf("ENTER pressed\n");
                x = xhome;
                y += u8g2_GetMaxCharHeight(&oled) + 1;
                break;
            case 0x7f:
                //printf("DEL pressed\n");
                if (x >= xhome + u8g2_GetMaxCharWidth(&oled)) {
                    x -= u8g2_GetMaxCharWidth(&oled) + 1;
                    u8g2_SetDrawColor(&oled, 0);
                    u8g2_DrawBox(&oled, x, y-u8g2_GetMaxCharHeight(&oled), u8g2_GetMaxCharWidth(&oled), u8g2_GetMaxCharHeight(&oled));
                    u8g2_SetDrawColor(&oled, 1);
                    u8g2_SendBuffer(&oled);
                }
                break;
            case 'U':
                //printf("UP pressed\n");
                y -= u8g2_GetMaxCharHeight(&oled) + 1;
                break;
            case 'D':
                //printf("DOWN pressed\n");
                y += u8g2_GetMaxCharWidth(&oled) + 1;
                break;
            default:
                //printf("DEFAULT\n");
                break;
        }
        printf("trying_xy=%i,%i\t", x, y);

        if (x > u8g2_GetDisplayWidth(&oled) - u8g2_GetMaxCharWidth(&oled)) {
            x = xhome;
            y += u8g2_GetMaxCharHeight(&oled) + 1;
        }
        if (y > u8g2_GetDisplayHeight(&oled)) {
            y = u8g2_GetMaxCharHeight(&oled) - 1;
            // u8g2_SetDrawColor(&oled, 0);
	        // u8g2_DrawBox(&oled, 80, 0, u8g2_GetDisplayWidth(&oled) - 80, u8g2_GetDisplayHeight(&oled)-1);
	        // u8g2_SetDrawColor(&oled, 1);
	        // u8g2_SendBuffer(&oled);
        }
        if (x < xhome) {
            x = xhome;
        }
        if (y < yhome) {
            y = yhome;
        }
        printf("new_xy=%i,%i\n", x, y);
    }
}


void button_test()
{
    if (buttons_changed) {
        buttons_changed = 0;
        printf("# button_test(): %02X\n", (mcp.readRegister(INTCAP)>>8) & 0x0f);
    }
}


void adc_test()
{
    if ( !(millis % 5000) ) {
        uint16_t ain0, ain1, ain2, ain3;
        float f0, f1, f2, f3;
        uint16_t i0, i1, i2, i3;

        ain0 = adc_read(0);
        ain1 = adc_read(1);
        ain2 = adc_read(2);
        ain3 = adc_read(3);

        f0 = 3.0 / 65536 * ain0;
        f1 = 3.0 / 65536 * ain1;
        f2 = 3.0 / 65536 * ain2;
        f3 = 3.0 / 65536 * ain3;

        i0 = 1000 * 3 * ain0 / 65536;
        i1 = 1000 * 3 * ain1 / 65536;
        i2 = 1000 * 3 * ain2 / 65536;
        i3 = 1000 * 3 * ain3 / 65536;

        //printf("ain[0..3]: %1.3f/0x%04X, %1.3f/0x%04X, %1.3f/0x%04X, %1.3f/0x%04X\n", f0, ain0, f1, ain1, f2, ain2, f3, ain3);
        //printf("ain[0..3]: %i/0x%04X, %i/0x%04X, %i/0x%04X, %i/0x%04X\n", (uint16_t)f0*1000, ain0, (uint16_t)f1*1000, ain1, (uint16_t)f2*1000, ain2, (uint16_t)f3*1000, ain3);
        printf("# adc_test(): ain[0..3]: %i/0x%04X, %i/0x%04X, %i/0x%04X, %i/0x%04X\n", i0, ain0, i1, ain1, i2, ain2, i3, ain3);
    }
}


void dac_test()
{
    static bool once = false;

    if (!once) {
        // FIXME: is Vref stable?
        // Set reference voltage (measured on VREF on the analog input connector)
        system_set_vref_voltage(2.936);

        // Set A to 1.50V
        mcp4728_write_voltage(MCP4728_CH_A, 1.50);

        once = true;
    }

    // Use the RNG to set a random voltage
    if ( !(millis % 100) ) {
        mcp4728_write(MCP4728_CH_B, (uint16_t)RNG->OR & 0xfff );
        mcp4728_write(MCP4728_CH_C, (uint16_t)RNG->OR & 0xfff );
        mcp4728_write(MCP4728_CH_D, (uint16_t)RNG->OR & 0xfff );
    }
}


void pwm_test()
{
    printf("# pwm_test(): \n");
    pwm_test_fade(&pwm0);
    pwm_test_fade(&pwm1);
    pwm_test_fade(&pwm2);
    pwm_test_fade(&pwm3);
}

void pwm_test_fade(PwmOut* pwm)
{
    float val;

    // Fade in
    for (val=0.0; val<=1.0; val+=0.005) {
        pwm->write(val);
        ThisThread::sleep_for(1ms);
    }    

    // Fade out
    for ( ; val>=0.0; val-=0.005) {
        pwm->write(val);
        ThisThread::sleep_for(1ms);
    }    
}

void dout_test()
{
    int16_t d;

    printf("# dout_test()\n");

    for (d=1; d<0b10000000; d<<=1) {
        dout_write(d);
        ThisThread::sleep_for(100ms);
    }
    
    d >>= 1;
    do {
        d >>= 1;
        dout_write(d);
        ThisThread::sleep_for(100ms);
    } while (d != 0);
}

void din_dout_test()
{
    static uint8_t d_prev;
    uint8_t d;
    
    d = din_read();
    dout_write(d);

    if ( !(millis % 500) ) {
        if (d != d_prev) {
            d_prev = d;
            printf("# din_dout_test(): 0x%02X\n", d);
        }
    }
}


