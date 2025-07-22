void delay_ms(int ms);
void delay_us(int us);
void uart_init(unsigned int baudrate);
void uart_tx(unsigned char ch);
void uart_tx_string(const char *str);
void spi_init(void);
void spi_write(char data);
char spi_read(void);

