#ifndef _MCP4728_H_
#define _MCP4728_H_

#include "board_freedom.h"

#define MCP4728_ADDRESS_DEFAULT                 (0x60<<1)
#define MCP4728_ADDRESS                         MCP4728_ADDRESS_DEFAULT
#define MCP4728_RESOLUTION_BITS                 (12U)
#define MCP4728_RESOLUTION                      (1<<MCP4728_RESOLUTION_BITS)

#define MCP4728_CH_A                            (0x00U)
#define MCP4728_CH_B                            (0x01U)
#define MCP4728_CH_C                            (0x02U)
#define MCP4728_CH_D                            (0x03U)


// Commands
#define MCP4728_CMD_FAST                        (0x00U)
#define MCP4728_CMD_MULTI                       (0x40U)
#define MCP4728_CMD_SEQ                         (0x50U)
#define MCP4728_CMD_SINGLE                      (0xA1U)
#define MCP4728_CMD_VREF                        (0x80U)
#define MCP4728_CMD_PD                          (0xA0U)
#define MCP4728_CMD_GAIN                        (0xC0U)

#define MCP4728_MULTI_DAC_A                     (0x00U)
#define MCP4728_MULTI_DAC_B                     (0x01U)
#define MCP4728_MULTI_DAC_C                     (0x02U)
#define MCP4728_MULTI_DAC_D                     (0x03U)

// Fast-write - to DAC
#define MCP4728_FAST_PD_MASK                    (0x30U)
#define MCP4728_FAST_PD_SHIFT                   (4U)
#define MCP4728_FAST_PD(x)                      (((uint8_t)(((uint8_t)(x)) << MCP4728_FAST_PD_SHIFT)) & MCP4728_FAST_PD_MASK)

// Multi-write - to DAC
#define MCP4728_MULTI_DAC_MASK                  (0x06U)
#define MCP4728_MULTI_DAC_SHIFT                 (1U)
#define MCP4728_MULTI_DAC(x)                    (((uint8_t)(((uint8_t)(x)) << MCP4728_MULTI_DAC_SHIFT)) & MCP4728_MULTI_DAC_MASK)

#define MCP4728_MULTI_UDAC_MASK                 (0x01U)
#define MCP4728_MULTI_UDAC_SHIFT                (0U)
#define MCP4728_MULTI_UDAC(x)                   (((uint8_t)(((uint8_t)(x)) << MCP4728_MULTI_UDAC_SHIFT)) & MCP4728_MULTI_UDAC_MASK)

#define MCP4728_MULTI_VREF_MASK                 (0x80U)
#define MCP4728_MULTI_VREF_SHIFT                (7U)
#define MCP4728_MULTI_VREF(x)                   (((uint8_t)(((uint8_t)(x)) << MCP4728_MULTI_VREF_SHIFT)) & MCP4728_MULTI_VREF_MASK)

#define MCP4728_MULTI_PD_MASK                   (0x60U)
#define MCP4728_MULTI_PD_SHIFT                  (5U)
#define MCP4728_MULTI_PD(x)                     (((uint8_t)(((uint8_t)(x)) << MCP4728_MULTI_PD_SHIFT)) & MCP4728_MULTI_PD_MASK)

#define MCP4728_MULTI_GAIN_MASK                 (0x10U)
#define MCP4728_MULTI_GAIN_SHIFT                (5U)
#define MCP4728_MULTI_GAIN(x)                   (((uint8_t)(((uint8_t)(x)) << MCP4728_MULTI_GAIN_SHIFT)) & MCP4728_MULTI_GAIN_MASK)

// Seq-write - to DAC and EEPROM
#define MCP4728_SEQ_DAC_MASK                    (0x06U)
#define MCP4728_SEQ_DAC_SHIFT                   (2U)
#define MCP4728_SEQ_DAC(x)                      (((uint8_t)(((uint8_t)(x)) << MCP4728_SEQ_DAC_SHIFT)) & MCP4728_SEQ_DAC_MASK)

#define MCP4728_SEQ_UDAC_MASK                   (0x01U)
#define MCP4728_SEQ_UDAC_SHIFT                  (0U)
#define MCP4728_SEQ_UDAC(x)                     (((uint8_t)(((uint8_t)(x)) << MCP4728_SEQ_UDAC_SHIFT)) & MCP4728_SEQ_UDAC_MASK)

// Single-write - To DAC and EEPROM
#define MCP4728_SINGLE_DAC_MASK                 (0x06U)
#define MCP4728_SINGLE_DAC_SHIFT                (2U)
#define MCP4728_SINGLE_DAC(x)                   (((uint8_t)(((uint8_t)(x)) << MCP4728_SINGLE_DAC_SHIFT)) & MCP4728_SINGLE_DAC_MASK)

#define MCP4728_SINGLE_UDAC_MASK                (0x01U)
#define MCP4728_SINGLE_UDAC_SHIFT               (0U)
#define MCP4728_SINGLE_UDAC(x)                  (((uint8_t)(((uint8_t)(x)) << MCP4728_SINGLE_UDAC_SHIFT)) & MCP4728_SINGLE_UDAC_MASK)

#define MCP4728_SINGLE_VREF_MASK                (0x80U)
#define MCP4728_SINGLE_VREF_SHIFT               (7U)
#define MCP4728_SINGLE_VREF(x)                  (((uint8_t)(((uint8_t)(x)) << MCP4728_SINGLE_VREF_SHIFT)) & MCP4728_SINGLE_VREF_MASK)

#define MCP4728_SINGLE_PD_MASK                  (0x60U)
#define MCP4728_SINGLE_PD_SHIFT                 (5U)
#define MCP4728_SINGLE_PD(x)                    (((uint8_t)(((uint8_t)(x)) << MCP4728_SINGLE_PD_SHIFT)) & MCP4728_SINGLE_PD_MASK)

#define MCP4728_SINGLE_GAIN_MASK                (0x10U)
#define MCP4728_SINGLE_GAIN_SHIFT               (5U)
#define MCP4728_SINGLE_GAIN(x)                  (((uint8_t)(((uint8_t)(x)) << MCP4728_SINGLE_GAIN_SHIFT)) & MCP4728_SINGLE_GAIN_MASK)

// Vref
#define MCP4728_VREF_MASK                       (0x0FU)
#define MCP4728_VREF_SHIFT                      (0U)
#define MCP4728_VREF(x)                         (((uint8_t)(((uint8_t)(x)) << MCP4728_VREF_SHIFT)) & MCP4728_VREF_MASK)

#define MCP4728_VREF_A_MASK                     (0x08U)
#define MCP4728_VREF_A_SHIFT                    (3U)
#define MCP4728_VREF_A(x)                       (((uint8_t)(((uint8_t)(x)) << MCP4728_VREF_A_SHIFT)) & MCP4728_VREF_A_MASK)

#define MCP4728_VREF_B_MASK                     (0x04U)
#define MCP4728_VREF_B_SHIFT                    (2U)
#define MCP4728_VREF_B(x)                       (((uint8_t)(((uint8_t)(x)) << MCP4728_VREF_B_SHIFT)) & MCP4728_VREF_B_MASK)

#define MCP4728_VREF_C_MASK                     (0x02U)
#define MCP4728_VREF_C_SHIFT                    (1U)
#define MCP4728_VREF_C(x)                       (((uint8_t)(((uint8_t)(x)) << MCP4728_VREF_C_SHIFT)) & MCP4728_VREF_C_MASK)

#define MCP4728_VREF_D_MASK                     (0x01U)
#define MCP4728_VREF_D_SHIFT                    (0U)
#define MCP4728_VREF_D(x)                       (((uint8_t)(((uint8_t)(x)) << MCP4728_VREF_D_SHIFT)) & MCP4728_VREF_D_MASK)

// Power-down
#define MCP4728_PD_A_MASK                       (0x0CU)
#define MCP4728_PD_A_SHIFT                      (2U)
#define MCP4728_PD_A(x)                         (((uint8_t)(((uint8_t)(x)) << MCP4728_PD_A_SHIFT)) & MCP4728_PD_A_MASK)

#define MCP4728_PD_B_MASK                       (0x00U)
#define MCP4728_PD_B_SHIFT                      (0U)
#define MCP4728_PD_B(x)                         (((uint8_t)(((uint8_t)(x)) << MCP4728_PD_B_SHIFT)) & MCP4728_PD_B_MASK)

#define MCP4728_PD_C_MASK                       (0xC0U)
#define MCP4728_PD_C_SHIFT                      (6U)
#define MCP4728_PD_C(x)                         (((uint8_t)(((uint8_t)(x)) << MCP4728_PD_C_SHIFT)) & MCP4728_PD_C_MASK)

#define MCP4728_PD_D_MASK                       (0x30U)
#define MCP4728_PD_D_SHIFT                      (4U)
#define MCP4728_PD_D(x)                         (((uint8_t)(((uint8_t)(x)) << MCP4728_PD_D_SHIFT)) & MCP4728_PD_D_MASK)

// Gain
#define MCP4728_GAIN_MASK                       (0x0FU)
#define MCP4728_GAIN_SHIFT                      (0U)
#define MCP4728_GAIN(x)                         (((uint8_t)(((uint8_t)(x)) << MCP4728_GAIN_SHIFT)) & MCP4728_GAIN_MASK)

#define MCP4728_GAIN_A_MASK                     (0x08U)
#define MCP4728_GAIN_A_SHIFT                    (3U)
#define MCP4728_GAIN_A(x)                       (((uint8_t)(((uint8_t)(x)) << MCP4728_GAIN_A_SHIFT)) & MCP4728_GAIN_A_MASK)

#define MCP4728_GAIN_B_MASK                     (0x04U)
#define MCP4728_GAIN_B_SHIFT                    (2U)
#define MCP4728_GAIN_B(x)                       (((uint8_t)(((uint8_t)(x)) << MCP4728_GAIN_B_SHIFT)) & MCP4728_GAIN_B_MASK)

#define MCP4728_GAIN_C_MASK                     (0x02U)
#define MCP4728_GAIN_C_SHIFT                    (1U)
#define MCP4728_GAIN_C(x)                       (((uint8_t)(((uint8_t)(x)) << MCP4728_GAIN_C_SHIFT)) & MCP4728_GAIN_C_MASK)

#define MCP4728_GAIN_D_MASK                     (0x01U)
#define MCP4728_GAIN_D_SHIFT                    (0U)
#define MCP4728_GAIN_D(x)                       (((uint8_t)(((uint8_t)(x)) << MCP4728_GAIN_D_SHIFT)) & MCP4728_GAIN_D_MASK)



extern float mcp4728_vref_voltage;

void mcp4728_init();
void mcp4728_write(uint8_t ch, uint16_t val);
void mcp4728_write_voltage(uint8_t ch, float voltage);

#endif
