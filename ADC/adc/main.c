#include <LPC214x.h>
#include <stdio.h>  // For sprintf()
#include"header.h"

unsigned int i ;
// Simple software delay (~1 ms per iteration)
void delay_ms(unsigned int ms) {
    for (i = 0; i < ms * 6000; i++);
}

int main(void) {
    unsigned int adc_val;
    float temperature;
    char buffer[40];

    uart_init();
    adc_init();
		uart_tx_string("vinod");
    while (1) {
        adc_val = adc_read();
        temperature = adc_to_temp(adc_val);

        sprintf(buffer, "Temp = %.2f C\r\n", temperature);
        uart_tx_string(buffer);

        delay_ms(1000);  // 1 second delay
    }
}
