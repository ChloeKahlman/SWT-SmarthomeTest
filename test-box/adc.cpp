#include "adc.h"

// See MK66F18.h in mbed-os dir for register names

static void adc0_config();
static void adc1_config();
static void adc0_calibrate();
static void adc1_calibrate();

adc_data_s adc_data;

void adc_init()
{
    // Enable ADC0 and ADC1 Clock Gate Control
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
    SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;

    adc0_config();
    adc0_calibrate();

    adc1_config();
    adc1_calibrate();
}

void adc0_config()
{
    // Uses the same settings as recommended for calibration (AVG=32, ADC_CLK<4MHz)
    // ADC_CLK = (BUSCLK/2) / 8 = (60/2)/8=3.75MHz. Max ADC_CLK is 24MHz however so a conversion just takes a little more time. Maybe more accurate though.
    ADC0->CFG1 = ADC_CFG1_ADIV(3) | ADC_CFG1_ADLSMP(0) | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(2);         // ADIV=1:8, ADSLMP=short, MODE=16bit, ADICLK=BUSCLK/2
    ADC0->CFG2 = ADC_CFG2_MUXSEL(0) | ADC_CFG2_ADACKEN(1) | ADC_CFG2_ADHSC(0) | ADC_CFG2_ADLSTS(0);     // MUX=ch_A, ADACKEN=en, ADHSC=normal, ADLSTS=default
    ADC0->SC2  = ADC_SC2_ADTRG(0) | ADC_SC2_ACFE(0) | ADC_SC2_ACFGT(0) | ADC_SC2_ACREN(0) | ADC_SC2_DMAEN(0) | ADC_SC2_REFSEL(0);   // ADTRG=soft_trig, ACFE=comp_dis, ACFGT=x, ACREN=x, DMAEN=dis, REFSEL=default
    ADC0->SC3  = ADC_SC3_CAL(0) | ADC_SC3_ADCO(0) | ADC_SC3_AVGE(1) | ADC_SC3_AVGS(3);                  // CAL=off, ADCO=single, AVGE=en, AVGS=32
    ADC0->SC1[0] = 16;          // Select ADC0_SE16 input, the only channel from ADC0 that's used on the Freedom Controller
}


void adc1_config()
{
    // Uses the same settings as recommended for calibration (AVG=32, ADC_CLK<4MHz)
    // ADC_CLK = (BUSCLK/2) / 8 = (60/2)/8=3.75MHz. Max ADC_CLK is 24MHz however so a conversion just takes a little more time. Maybe more accurate though.
    ADC1->CFG1 = ADC_CFG1_ADIV(3) | ADC_CFG1_ADLSMP(0) | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(2);         // ADIV=1:8, ADSLMP=short, MODE=16bit, ADICLK=BUSCLK/2
    ADC1->CFG2 = ADC_CFG2_MUXSEL(0) | ADC_CFG2_ADACKEN(1) | ADC_CFG2_ADHSC(0) | ADC_CFG2_ADLSTS(0);     // MUX=ch_A, ADACKEN=en, ADHSC=normal, ADLSTS=default
    ADC1->SC2  = ADC_SC2_ADTRG(0) | ADC_SC2_ACFE(0) | ADC_SC2_ACFGT(0) | ADC_SC2_ACREN(0) | ADC_SC2_DMAEN(0) | ADC_SC2_REFSEL(0);   // ADTRG=soft_trig, ACFE=comp_dis, ACFGT=x, ACREN=x, DMAEN=dis, REFSEL=default
    ADC1->SC3  = ADC_SC3_CAL(0) | ADC_SC3_ADCO(0) | ADC_SC3_AVGE(1) | ADC_SC3_AVGS(3);                  // CAL=off, ADCO=single, AVGE=en, AVGS=32
    // No default channel selected, since it's switched in the adc_read function
}


void adc0_calibrate()
{
    uint16_t gcal = 0;      // Gain calibration

    printf("# adc0_calibrate()\n");

    //
    // Assuming ADC is already setup for calibration in adcX_config
    //

    // Start calibration
    printf("ADC0 start cal\n");
    ADC0->SC3 |= ADC_SC3_CAL_MASK;

    // Wait for end of conversion
    while ( !(ADC0->SC1[0] & ADC_SC1_COCO_MASK) );

    // Check for cal error
    if ( ADC0->SC1[0] & ADC_SC3_CALF_MASK ) {
        printf("ADC0 cal error\n");
    } else {
        printf("ADC0 cal ok, setting Gain cal\n");
        gcal = ADC0->CLP0 + ADC0->CLP1 + ADC0->CLP2 + ADC0->CLP3 + ADC0->CLP4 + ADC0->CLPS;
        gcal >>= 1;
        gcal |= 0x8000;
        ADC0->PG = gcal;

        gcal = ADC0->CLM0 + ADC0->CLM1 + ADC0->CLM2 + ADC0->CLM3 + ADC0->CLM4 + ADC0->CLMS;
        gcal >>= 1;
        gcal |= 0x8000;
        ADC0->MG = gcal;
    }

    printf("ADC0 PG=%04X, PM=%04X\n", ADC0->PG, ADC0->MG);
}


void adc1_calibrate()
{
    uint16_t gcal = 0;      // Gain calibration

    //
    // Assuming ADC is already setup for calibration in adcX_config
    //

    printf("# adc1_calibrate()\n");

    // Start calibration
    printf("ADC0 start cal\n");
    ADC0->SC3 |= ADC_SC3_CAL_MASK;

    // Wait for end of conversion
    while ( !(ADC0->SC1[0] & ADC_SC1_COCO_MASK) );

    // Check for cal error
    if ( ADC0->SC1[0] & ADC_SC3_CALF_MASK ) {
        printf("ADC0 cal error\n");
    } else {
        printf("ADC0 cal ok, setting Gain cal\n");
        gcal = ADC0->CLP0 + ADC0->CLP1 + ADC0->CLP2 + ADC0->CLP3 + ADC0->CLP4 + ADC0->CLPS;
        gcal >>= 1;
        gcal |= 0x8000;
        ADC0->PG = gcal;

        gcal = ADC0->CLM0 + ADC0->CLM1 + ADC0->CLM2 + ADC0->CLM3 + ADC0->CLM4 + ADC0->CLMS;
        gcal >>= 1;
        gcal |= 0x8000;
        ADC0->MG = gcal;
    }

    printf("ADC0 PG=%04X, PM=%04X\n", ADC0->PG, ADC0->MG);
}


uint16_t adc_read(uint8_t freedom_ain_channel)
{
    uint16_t adc_res;
    uint8_t ch_map[4] = {16, 16, 18, 23};       // Maps freedom_ain_channel to actual ADC0/1 channels

    // 
    freedom_ain_channel &= 0x03;

    if (freedom_ain_channel == 0) {
        // ADC0: ADC0_SE16
        // In software trigger mode, a write to SC1A starts a conversion.
        ADC0->SC1[0] = ADC_SC1_ADCH( ch_map[freedom_ain_channel] );
        // Wait for conversion_complete flag
        while ( !(ADC0->SC1[0] & ADC_SC1_COCO_MASK) );
        adc_res = ADC0->R[0];
    } else {
        // ADC1: ADC1_SE16 / ADC1_SE18 / ADC1_SE23
        ADC1->SC1[0] = ADC_SC1_ADCH( ch_map[freedom_ain_channel] );
        while ( !(ADC1->SC1[0] & ADC_SC1_COCO_MASK) );
        adc_res = ADC1->R[0];
    }
    return adc_res;
}


// FIXME: untested
void adc_readall(adc_data_s* adc_data)
{
    uint8_t ch;
    for (ch=0; ch<4; ch++) {
        adc_data->data[ch] = adc_read(ch);
        adc_data->val[ch]  = adc_data->data[ch] * system_vref_voltage / ADC_RESOLUTION;
    }
}

