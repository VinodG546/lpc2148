void init_lcd(void);
void sendcmd(unsigned int cmd);
void senddata(unsigned char data);
void delay_ms(int ms);
void delay_us(int us);
void adc_init(void) ;
unsigned int adc_read(void);
float adc_to_temp(unsigned int adc_val);
void floatlcd(float f,int ndp);

