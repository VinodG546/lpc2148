#include<LPC214X.h>
#include<stdio.h>
#include"header.h"
#include"timer.h"
int main(){
	unsigned char read_val;
	char buffer[30];
	
	uart_init(9600);
	uart_tx_string("vinod");
	i2c_init();
	
	i2c_start();
	i2c_write(0XA0);
	i2c_write(0x00);
	i2c_write('A');
	i2c_stop();
	
	delay_ms(10);
	
	i2c_start();
	i2c_write(0XA0);
	i2c_write(0x00);
	i2c_start();
	i2c_write(0xA1);
	read_val=i2c_read_nack();
	i2c_stop();
	
	sprintf(buffer,"READ:%c\r\n",read_val);
	uart_tx_string(buffer);
	
	while(1);
}



