#include<LPC214X.h>
#include"header.h"

// ADC0.1 (P0.28 / Pin 13) Initialization
void adc_init(void) {
    PINSEL1 |= (1 << 24);      // Set P0.28 to function AD0.1
    AD0CR = (1 << 1) |         // Select channel 1 (AD0.1)
            (4 << 8) |         // CLKDIV = PCLK/5
            (1 << 21);         // Enable ADC
}

// Read ADC0.1 (P0.28)
unsigned int adc_read(void) {
    AD0CR |= (1 << 24);               // Start conversion
    while (!(AD0GDR & (1U << 31)));   // Wait for DONE bit
    return (AD0GDR >> 6) & 0x3FF;     // Extract 10-bit result
}

// Convert ADC value to temperature in °C
float adc_to_temp(unsigned int adc_val) {
    float voltage = (adc_val * 3.3) / 1023.0;  // Voltage in volts
    return voltage * 100.0;                   // LM35: 10mV per °C
}
