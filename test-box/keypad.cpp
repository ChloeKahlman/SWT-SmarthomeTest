#include "keypad.h"

Ticker keypad_scan_ticker;
uint8_t keypad_key = 0;
bool keypad_keypress = false;
bool keypad_scan_go = false;
bool keypad_isr_go = false;


void keypad_init()
{
    keypad_scan_ticker.attach(&keypad_set_scan_flag, KEYPAD_SCAN_RATE_MS);
    mcp.write_mask(0x00, 0b00111100);               // Set all column bits to zero
}


// The I2C library isn't thread or interrupt safe, so just set a flag and run it from main (?)
void keypad_set_scan_flag()
{
    keypad_scan_go = true;
}


uint8_t keypad_scan()
{
    // Only run when told so by the ticker flag
    if (keypad_scan_go == false) {
        return 0;
    }
    keypad_scan_go = false;

    int col;
    int row;
    int key;
    const int col_mask = 0b00111100;
    const int row_mask = 0b11000011;
    static bool key_released = true;

    // Read row bits. If all zero, no key is pressed (assuming all column bits are already zero, which they should)
    row = mcp.read_mask(row_mask);                      // Read row values
    if (row == 0x00) {
        key_released = true;
        // No key pressed, or keypress not processed
    } 
    if (row != 0x00 && key_released == true) {
        // Key pressed, scan it
        key_released = false;
        if (keypad_keypress == 0) {
            col = 0b00011100;
            mcp.write_mask(col, col_mask);
            row = mcp.read_mask(0b11000011);
            if ( row != 0) {
                keypad_keypress = 1;
            }
        }

        if (keypad_keypress == 0) {
            col = 0b00101100;
            mcp.write_mask(col, col_mask);
            row = mcp.read_mask(0b11000011);
            if ( row != 0) {
                keypad_keypress = 1;
            }
        }

        if (keypad_keypress == 0) {
            col = 0b00110100;
            mcp.write_mask(col, col_mask);
            row = mcp.read_mask(0b11000011);
            if ( row != 0) {
                keypad_keypress = 1;
            }
        }

        if (keypad_keypress == 0) {
            col = 0b00111000;
            mcp.write_mask(col, col_mask);
            row = mcp.read_mask(0b11000011);
            if ( row != 0) {
                keypad_keypress = 1;
            }
        }
        mcp.write_mask(0b00000000, col_mask);           // All columns zero again

        key = row | col;
        keypad_keypress = 1;
        //printf("kp: %02x\n", key);                      // Shows raw key codes
 
#if KEYPRESS_BEEP_ENABLED == true
        buzz = 1;
        thread_sleep_for(KEYPRESS_BEEP_LENGTH_MS);
        buzz = 0;
#endif

        switch(key) {
            case 0x74:
                key = KEYPAD_KEY_0;
                break;
            case 0x39:
                key = KEYPAD_KEY_1;
                break;
            case 0x35:
                key = KEYPAD_KEY_2;
                break;
            case 0x2d:
                key = KEYPAD_KEY_3;
                break;
            case 0x3a:
                key = KEYPAD_KEY_4;
                break;
            case 0x36:
                key = KEYPAD_KEY_5;
                break;
            case 0x2e:
                key = KEYPAD_KEY_6;
                break;
            case 0xb8:
                key = KEYPAD_KEY_7;
                break;
            case 0xb4:
                key = KEYPAD_KEY_8;
                break;
            case 0xac:
                key = KEYPAD_KEY_9;
                break;
            case 0x1d:
                key = KEYPAD_KEY_UP;
                break;
            case 0x1e:
                key = KEYPAD_KEY_DOWN;
                break;
            case 0x9c:
                key = KEYPAD_KEY_DEL;
                break;
            case 0x5c:
                key = KEYPAD_KEY_ENTER;
                break;
            case 0x6c:
                key = KEYPAD_KEY_DOT;
                break;
            case 0x78:
                key = KEYPAD_KEY_ESC;
                break;
            default:
                key = 0x00;
                break;
        }
        keypad_key = key;
        return key;
    }
    return 0;
}

