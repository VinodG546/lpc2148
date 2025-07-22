void i2c_init(void);
void i2c_start(void);
void i2c_write(char );
unsigned char i2c_read_ack(void);
unsigned char i2c_read_nack(void);
void i2c_multiread(char *arr,int bytes);
void i2c_stop(void);
void delay_ms(int );
void delay_us(int);
void uart_init(unsigned int baudrate);
void uart_tx(unsigned char ch);
void uart_tx_string(const char *str);

