void adc_init(void);
unsigned int adc_read(void);
float adc_to_temp(unsigned int adc_val);
void uart_init(void);
void uart_tx(char ch);
void uart_tx_string(const char *str);

