#include "board_freedom.h"
#include "i2cscan.h"
#include "oled_ssd1322.h"


int i2c_scan_linuxy(I2C* i2cbus)
{
	int ack;
	int devFound = 0;

    printf("# i2c_scan: scan 0x03...0x77\n");
    printf("# Note that the Arm Mbed API uses 8-bit addresses, so left-shift the addresses by 1 bit in your code\n");
    printf("     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
    printf("00:         ");

	for (int address = 0x03; address < 0x77; address++) {
		if (address % 0x10 == 0) {
			printf("\r\n%02X:", address & 0xF0);
		}
		//-- i2c.start();
		ack = i2cbus->write((address<<1), "11", 1);
		//-- i2c.stop();
		if (ack == 0) { // device found
			printf(" %02X", address);
			devFound++;
		} else {
			printf(" --");
		}
	}
	printf("\r\nTotal %d device(s) found\r\n", devFound);
    return devFound;
}

// Same as above but shows the devices on the oled screen
int i2c_scan_oled(I2C* i2cbus)
{
	int ack;
	int devFound = 0;
	int posx, posy;
	char oled_text[80];

	// Oled header text
	u8g2_SetFont(&oled, u8g2_font_nokiafc22_tr);
	u8g2_DrawUTF8(&oled, 80, 7, "I2C device list:");

    printf("# i2c_scan: scan 0x03...0x77\n");
    printf("# Note that the Arm Mbed API uses 8-bit addresses, so left-shift the addresses by 1 bit in your code\n");
    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
    printf("00:         ");

	// Cursor position
	posx = 80;
	posy = 15;

	for (int address = 0x03; address < 0x77; address++) {
		if (address % 0x10 == 0) {
			printf("\r\n%02x:", address & 0xF0);
		}
		//-- i2c.start();
		ack = i2cbus->write((address<<1), "11", 1);
		//-- i2c.stop();
		if (ack == 0) {
			// device found
			printf(" %02x", address);
			devFound++;

			snprintf(oled_text, sizeof(oled_text), "%02x", address);
			u8g2_DrawUTF8(&oled, posx, posy, oled_text);

			// New cursor position. Font is 8x8 (FIXME: is it?) so x increment = 2*8 + space = 24
			posx += 20;	// 20 looks nicer
			// Check if we need a new line
			if (posx > (u8g2_GetDisplayWidth(&oled) - 16)) {
				posx = 80;		// 'cr'
				posy += 8;		// 'lf'
			}
			// Check if we're running out of screen space
			if (posy > u8g2_GetDisplayHeight(&oled)) {
				// just overwrite the same last line
				posx = 80;
				posy -= 8;
			}
		} else {
			printf(" --");
		}
	}
	printf("\r\nTotal %d device(s) found\r\n", devFound);

	// Update display
	u8g2_SendBuffer(&oled);
	thread_sleep_for(5000);

	// Clear text area by overwriting it with a black rect
	u8g2_SetDrawColor(&oled, 0);
	u8g2_DrawBox(&oled, 80, 0, u8g2_GetDisplayWidth(&oled) - 80, 63);
	u8g2_SetDrawColor(&oled, 1);
	u8g2_SendBuffer(&oled);
    return devFound;
}
