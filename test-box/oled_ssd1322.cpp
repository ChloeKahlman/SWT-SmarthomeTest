#include <u8g2.h>
#include "oled_ssd1322.h"


// OLED display
u8g2_t oled;

void oled_init() {
	// Init display. Rotate 180deg with U8G2_R2, u8g2_SetFlipMode() doesn't work on this display controller
    u8g2_Setup_ssd1322_nhd_256x64_f(&oled, U8G2_R2, u8x8_byte_k66f_3wire_hw_spi, u8x8_gpio_and_delay_mbed);
	u8g2_InitDisplay(&oled);
	u8g2_SetPowerSave(&oled, 1);
	u8g2_ClearBuffer(&oled);
	u8g2_SendBuffer(&oled);
	u8g2_SetPowerSave(&oled, 0);
}

void oled_splash(void)
{
	char oled_text[80];

	// Every pixel on
	u8g2_SetPowerSave(&oled, 1);		// Display off
	u8g2_ClearBuffer(&oled);
	u8g2_DrawBox(&oled, 0, 0, u8g2_GetDisplayWidth(&oled), u8g2_GetDisplayHeight(&oled));
	u8g2_SendBuffer(&oled);
	u8g2_SetPowerSave(&oled, 0);		// Display on
	thread_sleep_for(1000);

	// Blank screen
	u8g2_SetPowerSave(&oled, 1);
	u8g2_ClearBuffer(&oled);
	thread_sleep_for(1000);

	// Intro text
	u8g2_SetFont(&oled, u8g2_font_nokiafc22_tr);
	//u8g2_SetFont(&oled, SmallFont);
	u8g2_DrawXBM(&oled, 0, 0, vukip_logo_h64_width, vukip_logo_h64_height, vukip_logo_h64_bits);
	u8g2_DrawLine(&oled, 76, 0, 76, 63);
	u8g2_DrawUTF8(&oled, 80, 7, "Freedom Controller FRDM-K66F");

	snprintf(oled_text, sizeof(oled_text), "Build: %s %s", __DATE__, __TIME__);
	u8g2_DrawUTF8(&oled, 80, 15, oled_text);

	snprintf(oled_text, sizeof(oled_text), "Elektronica Beta VU");
	u8g2_DrawUTF8(&oled, 80, 23, oled_text);

	u8g2_SendBuffer(&oled);
	u8g2_SetPowerSave(&oled, 0);			// Display On
	thread_sleep_for(2500);

	// Swap vukip for BugZoo logo
	u8g2_DrawXBM(&oled, 0, 0, bugzoo_logo_h64_width, bugzoo_logo_h64_height, bugzoo_logo_h64_bits);
	u8g2_SendBuffer(&oled);
	thread_sleep_for(2500);

	//u8g2_SetPowerSave(&oled, 1);			// Display Off
	//u8g2_ClearDisplay(&oled);
	//u8g2_SetPowerSave(&oled, 0);			// Display On

	// Keep logo on display, just overwrite text area with a black box
	u8g2_SetDrawColor(&oled, 0);
	u8g2_DrawBox(&oled, 80, 0, u8g2_GetDisplayWidth(&oled) - 80, u8g2_GetDisplayHeight(&oled)-1);
	u8g2_SetDrawColor(&oled, 1);
	u8g2_SendBuffer(&oled);
}
