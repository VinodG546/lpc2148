void delay_ms(int);
void delay_us(int);
void uart_init(unsigned int);
void uart_tx(unsigned char);
void uart_tx_string(const char*);
unsigned char uart_rx(void);
