#include "board_freedom.h"

Ticker millis_ticker;
uint32_t millis = 0;            // +1 every ms

SPI spi0(PTD2, NC, PTD1);       // MOSI, MISO, SLCK   -  to SSD1322 OLED display
SPI spi1(PTD6, PTD7, PTD5);     // MOSI, MISO, SLCK   -  to nRF or WIFI module
I2C i2c(PTC11, PTC10);          // SDA, SCL - Freedom Controller and external bus
I2C i2c0(PTD9, PTD8);           // SDA, SCL - FRDM-K66F board local bus (accelerometer)
MCP23017 mcp(PTC11, PTC10, MCP23017_FRONT_ADDRESS);     // SDA, SCL. But for what?
//MCP4728 dac(&i2c, MCP4728_ADDRESS, MCP4728_VDD);

float system_vref_voltage = SYSTEM_VREF_VOLTAGE_DEFAULT;


DigitalOut led_board_red(LED1);
DigitalOut led_board_green(LED2);
DigitalOut led_board_blue(LED3);
DigitalOut led_fp_sw(PTD13);
DigitalOut led_fp_red(PTB2);
DigitalOut led_fp_green(PTB3);
DigitalOut buzz(PTC8);

DigitalIn button_0(PTB5);
DigitalIn button_1(PTB6);
DigitalIn button_2(PTB7);
DigitalIn button_3(PTC16);

DigitalOut dout0(PTA8);
DigitalOut dout1(PTA9);
DigitalOut dout2(PTB18);
DigitalOut dout3(PTC7);
DigitalOut dout4(PTB11);
DigitalOut dout5(PTE24);
DigitalOut dout6(PTC12);

DigitalIn  din0(PTA27);
DigitalIn  din1(PTA1);
DigitalIn  din2(PTB19);
DigitalIn  din3(PTA25);
DigitalIn  din4(PTB10);
DigitalIn  din5(PTE25);
DigitalIn  din6(PTA4);

PwmOut     pwm0(PTC2);
PwmOut     pwm1(PTC5);
PwmOut     pwm2(PTA6);
PwmOut     pwm3(PTA7);

// FIXME: Something is wrong with these pin 'numbers'
//AnalogIn ain0(ADC0_SE16);
//AnalogIn ain1(ADC1_SE16);
//AnalogIn ain2(ADC1_SE18);
//AnalogIn ain3(ADC1_SE23);

DigitalOut  oled_cs(PTC0);
DigitalOut  i2c_buff_nen(PTD12);     // /EN pin on the TCA9406 I2C buffer (inverted: 0=enable, 1=disable)
InterruptIn mcp_int_a(PTA26);
InterruptIn mcp_int_b(PTB23);

// LEDs on FRDM-K66F board
DigitalOut BOARD_LED_RED(LED1);     // PTC9
DigitalOut BOARD_LED_GREEN(LED2);   // PTE6
DigitalOut BOARD_LED_BLUE(LED3);    // PTA11


void freedom_board_init();
void freedom_millis_init();
void freedom_millis_ticker();

void freedom_gpio_init();
void freedom_spi_init();
void freedom_i2c_init();
void freedom_pwm_init();
void freedom_mcp23017_init();
void freedom_oled_init();
void freedom_adc_init();
void freedom_dac_init();
void freedom_rtc_init();
void freedom_keypad_init();
void freedom_button_init();
void freedom_rng_init();


void board_init()
{
    freedom_board_init();
}


void freedom_board_init()
{
    freedom_millis_init();
    freedom_gpio_init();
    freedom_pwm_init();
    freedom_spi_init();
    freedom_i2c_init();
    freedom_mcp23017_init();
    freedom_adc_init();
    freedom_dac_init();
    freedom_rtc_init();
    freedom_oled_init();
    freedom_keypad_init();
    freedom_button_init();
    freedom_rng_init();
}

void freedom_millis_init()
{
    millis_ticker.attach(&freedom_millis_ticker, 1ms);
}


// +1 every 1ms
void freedom_millis_ticker()
{
    millis++;
}


void freedom_gpio_init()
{
    led_board_red = 1;
    led_board_green = 1;
    led_board_blue = 1;
    
    dout0 = 0;
    dout1 = 0;
    dout2 = 0;
    dout3 = 0;
    dout4 = 0;
    dout5 = 0;
    dout6 = 0;

    din0.mode(PullDown);        // Enable pull-down resistor on input
    din1.mode(PullDown);
    din2.mode(PullDown);
    din3.mode(PullDown);
    din4.mode(PullDown);
    din5.mode(PullDown);
    din6.mode(PullUp);          // This one has a pull-up resistor (could be used as /NMI pin (?) )
}


void freedom_spi_init()
{
    spi0.format(9, 0);              // 9-bits SPI data, mode 0
    spi0.frequency(10000000);       // SPI freq 10MHz
}

// Turn on/off time for the BTS716G driver is about 100us(typical), so PWM period should probably not be less than 1ms (Fpwm=1kHz)
void freedom_pwm_init()
{
    pwm0.write(0.0);
    pwm1.write(0.0);
    pwm2.write(0.0);
    pwm3.write(0.0);
    pwm0.period_ms(10);
    pwm1.period_ms(10);
    pwm2.period_ms(10);
    pwm3.period_ms(10);
}


void freedom_i2c_init()
{
    i2c.frequency(400000);          // I2C bus freq 400kHz
    i2c_buff_nen = 1;               // External I2C bus disabled
}


void freedom_mcp23017_init()
{
    mcp.reset();
    mcp.config( (MCP_GPB_DIR<<8) | MCP_GPA_DIR, (MCP_GPB_PULL<<8) | MCP_GPA_PULL, (MCP_GPB_POL<<8) | MCP_GPA_POL);      // Config direction, pullups and polarity
    mcp.digitalWordWrite( (MCP_GPB_VAL<<8) | MCP_GPA_VAL);                      // Set output values
    mcp.writeRegister( GPINTEN, (uint16_t)((MCP_GPB_INT<<8) | MCP_GPA_INT) );   // Set interrupt pins
}


void freedom_oled_init()
{
    oled_init();
}


void freedom_adc_init()
{
    // TODO - those damn ADC pins and their hardfaults
    adc_init();
}


void freedom_dac_init()
{
    mcp4728_init();
}


void freedom_rtc_init()
{
    // TODO - when the DS3231M is available again
}

void freedom_keypad_init()
{
    keypad_init();
}

void freedom_button_init()
{
    button_init();
}


void freedom_rng_init()
{
    // Start RNG
    SIM->SCGC3 |= SIM_SCGC3_RNGA(1);
    RNG->CR = RNG_CR_CLRI(1) | RNG_CR_GO(1);
}

void dout_write(uint8_t db)
{
    dout0 = db & ( 1 << 0);
    dout1 = db & ( 1 << 1);
    dout2 = db & ( 1 << 2);
    dout3 = db & ( 1 << 3);
    dout4 = db & ( 1 << 4);
    dout5 = db & ( 1 << 5);
    dout6 = db & ( 1 << 6);
}


uint8_t din_read()
{
    return (din6<<6 | din5<<5 | din4<<4 | din3<<3 | din2<<2 | din1<<1 | din0<<0);
}


void system_set_vref_voltage(float vref)
{
    system_vref_voltage = vref;
}
