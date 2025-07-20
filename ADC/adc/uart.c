#include<LPC21XX.h>
#include"header.h"
// UART0 Initialization @ 9600 baud
void uart_init(void) {
    PINSEL0 |= (1 << 0) | (1 << 2);  // Enable UART0 TXD (P0.0), RXD (P0.1)
    U0LCR = 0x83;                   // 8-bit, 1 stop bit, enable DLAB
    U0DLM = 0;
    U0DLL = 97;                    // 9600 baud at 15 MHz PCLK
    U0LCR = 0x03;                  // Disable DLAB
}

// UART transmit character
void uart_tx(char ch) {
    while (!(U0LSR & (1 << 5)));  // Wait until THR is empty
    U0THR = ch;
}

// UART transmit string
void uart_tx_string(const char *str) {
    while (*str) {
        uart_tx(*str++);
    }
}
