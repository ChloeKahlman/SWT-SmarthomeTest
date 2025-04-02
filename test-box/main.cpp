
#include <cstdio>
#include <mbed.h>
#include "board_freedom.h"
#include "board_freedom_test.h"
#include "i2cscan.h"
#include "mcp4728.h"
#include "oled_ssd1322.h"
#include "adc.h"

// Extra OS debug. Triggers mbed-os recompilation if changed.
#if(1)
#define MBED_CONF_PLATFORM_ERROR_FILENAME_CAPTURE_ENABLED   1
#define MBED_CONF_PLATFORM_ERROR_HIST_ENABLED               1
#endif

#define MBED_CONF_PLATFORM_MINIMAL_PRINTF_ENABLE_FLOATING_POINT               1
#define MBED_CONF_PLATFORM_STDIO_BAUD_RATE 115200

const char _prog_name[]="Bugzoo_Freedom_Controller_frdm-k66f";
const int _prog_ver_major = 0;
const int _prog_ver_minor = 1;

DigitalIn greenButton(PTB5);
DigitalIn blueButton(PTB6);
DigitalIn redButton(PTB7);
DigitalIn blackButton(PTC16);

void demo() {
    
    buzz = 1;
    thread_sleep_for(10);
    buzz = 0;

    // Test te OLED screen is working
    oled_splash();

    // Test the on-board LEDS
    blinkenlights();

    // Test the digital outputs
    dout_test();

    // Scan the external I2C bus
    printf("Scanning Freedom Controller I2C bus (external):\n");
    i2c_scan_oled(&i2c);
    printf("\n");

    // Scan the internal I2C bus
    printf("Scanning FRDM-K66F I2C bus (internal):\n");
    i2c_scan_oled(&i2c0);
    printf("\n");
    // i2c_scan_linuxy(&i2c0);

    // Test PWM output
    pwm_test();

    // Make switch do blinky
    task_blinky_switch_init();    
}

void poll_analog(int * values) {
    for (int i = 0; i < 4; i++) {
        values[i] = adc_read(i);
    }
}

void set_pwm(int * values) {
    PwmOut * outputs[4] = {&pwm3, &pwm2, &pwm1, &pwm0};

    for (int i = 0; i < 4; i++) {
        float intensity = values[i] / 65535.0;
        if (intensity < 0.02) {
            intensity = 0;
        } else if (intensity > 0.98) {
            intensity = 1;
        }
        outputs[i]->write(intensity);
        printf("%d\t", (int)(intensity * 1000));
    }
    printf("\n");

}

void button_test_main(){
    if ( !(millis % 5000) ) {
        printf("# button_test():\t");

        if (greenButton){
            printf("Green button OFF\t");
        } else {
            printf("Green button ON \t");
        }

        if (redButton){
            printf("Red button OFF\t");
        } else {
            printf("Red button ON \t");
        }

        if (blueButton){
            printf("Blue button OFF\t");
        } else {
            printf("Blue button ON \t");
        }

        if (blackButton){
            printf("Black button OFF\t");
        } else {
            printf("Black button ON \t");
        }
        printf("\n");
    }
}

int main() {
    board_init();
    thread_sleep_for(10);

    printf("# %s - Ver %i.%i - Compiled %s %s \n", _prog_name, _prog_ver_major, _prog_ver_minor, __DATE__, __TIME__ );
    printf("This is %f\n", 3.1234567);

    if (redButton == 0 && blackButton == 0) {
        demo();
    }

	// Ready!
	u8g2_SetFont(&oled, u8g2_font_nokiafc22_tr);
	u8g2_DrawUTF8(&oled, 80, 7, "** Ready **");
	u8g2_SendBuffer(&oled);

    while(1) { 
        // led_fp_green = 1;
        // ThisThread::sleep_for(1ms);
        // led_fp_green = 0;
        // ThisThread::sleep_for(499ms);

        keypad_test_oled();
        adc_test();
        dac_test();
        din_dout_test();
        button_test_main();
        

        // int values[4];
        // poll_analog(values);
        // set_pwm(values);


    }

    return 0;
}




