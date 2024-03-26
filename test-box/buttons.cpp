#include "buttons.h"
#include "board_freedom.h"

volatile bool buttons_changed = false;

void button_init()
{
    button_0.mode(PullUp); 
    button_1.mode(PullUp); 
    button_2.mode(PullUp); 
    button_3.mode(PullUp); 

    mcp_int_b.fall(&button_isr);
}


void button_isr()
{
    buttons_changed = true;
}

// nr = 0, 1, 2 or 3
bool button_get_state(uint8_t nr)
{
    uint8_t buttons;

    //buttons = (mcp.digitalWordRead() >> 8) & 0x0f;
    //return (buttons >> nr) & 0x01;

    return mcp.read_bit(8+nr);
}

uint8_t button_get_all()
{
    return (mcp.digitalWordRead() >> 8) & 0x0f;
}


