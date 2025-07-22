#include<LPC214X.h>
void spi_init(){
	PINSEL0|=0x1500;//gpio pins of p0.4,p0.5,p0.6,p0.7
	S0SPCR = 0x20;//spi master mode ,8bit data ,spi0 mode
	S0SPCCR = 0x10;//even number, minimum value,pre scalar for spi clock
}

void spi_write(char data){
	char flush;
	IO0CLR = 1<<7;//enable spi communication with slave
	S0SPDR=data;//load data to be written in data reg
	while((S0SPDR & 0x80)==0);
	flush = S0SPDR;
	IO0SET = 1<<7;
}

char spi_read()
{
	IO0CLR = (1<<7);  /* SSEL = 0, enable SPI communication with slave */
	S0SPDR = 0xFF;  /* Transmit Flush byte */
	while ( (S0SPSR & 0x80) == 0 );  /* Wait till data transmission is completed */
	IO0SET = (1<<7);  /* SSEL = 1, disable SPI communication with slave */
	return S0SPDR;  /* Return the data received */
}

