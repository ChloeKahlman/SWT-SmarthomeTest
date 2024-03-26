#include "board_freedom.h"

void mcp4728_init()
{
    char  buf[8];
    uint16_t val;

    // Reference voltage = VDD
    buf[0] = MCP4728_CMD_VREF | MCP4728_VREF(0); 
    i2c.write(MCP4728_ADDRESS, buf, 1);

    // Powerdown = normal
    buf[0] = MCP4728_CMD_PD | MCP4728_PD_A(0) | MCP4728_PD_B(0);
    buf[1] = MCP4728_PD_C(0) | MCP4728_PD_D(0);
    i2c.write(MCP4728_ADDRESS, buf, 2);

    // Gain = 1
    buf[0] = MCP4728_CMD_GAIN | MCP4728_GAIN(0);
    i2c.write(MCP4728_ADDRESS, buf, 1);

    // Vout = 0 (all channels, fast write)
    val = 0;
    buf[0] = MCP4728_CMD_FAST | MCP4728_FAST_PD(0) | val >> 8;      // A hi, b11..b8
    buf[1] = val & 0xff;                                            // A lo, b7..b0
    buf[2] = MCP4728_FAST_PD(0) | val >> 8;                         // B hi
    buf[3] = val & 0xff;                                            // B lo
    buf[4] = MCP4728_FAST_PD(0) | val >> 8;                         // C hi
    buf[5] = val & 0xff;                                            // C lo
    buf[6] = MCP4728_FAST_PD(0) | val >> 8;                         // D hi
    buf[7] = val & 0xff;                                            // D lo
    i2c.write(MCP4728_ADDRESS, buf, 8);
}


void mcp4728_write(uint8_t ch, uint16_t val)
{
    char buf[3];

    // One channel, multi-write
    ch &= 0x03;
    val &= 0xfff;
    buf[0] = MCP4728_CMD_MULTI | MCP4728_MULTI_DAC(ch) | MCP4728_MULTI_UDAC(0);
    buf[1] = MCP4728_MULTI_VREF(0) | MCP4728_MULTI_PD(0) | MCP4728_MULTI_GAIN(0) | val >> 8;    // hi
    buf[2] = val & 0xff;                                            // lo
    i2c.write(MCP4728_ADDRESS, buf, 3);
}


void mcp4728_write_voltage(uint8_t ch, float voltage)
{
    uint16_t val;

    val = (uint16_t)(voltage * 0xfff / system_vref_voltage);
    mcp4728_write(ch, val);
}

