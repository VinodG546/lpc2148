#include<LPC214X.h>

void uart_init(unsigned int baudrate) {
    PINSEL0 |= 0x05;       // Enable UART0 (P0.0 & P0.1)
    U0LCR = 0x83;          // 8-bit, enable DLAB
    U0DLL = 97;            // For 9600 baud @ 15MHz PCLK
    U0LCR = 0x03;          // Disable DLAB
}

void uart_tx(unsigned char ch) {
    while(!(U0LSR & 0x20));
    U0THR = ch;
}

void uart_tx_string(const char *str) {
    while(*str) {
        uart_tx(*str++);
    }
}

