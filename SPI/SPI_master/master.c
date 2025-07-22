#include<LPC214X.h>
#include"header.h"
#include"timer.h"
int main(){
	char data_rx;
	uart_init(9600);
	spi_init();
	
	uart_tx_string("spi_master");
	
	spi_write('a');
	delay_ms(10);
	//char data_rx=spi_read();
	data_rx=spi_read();
	uart_tx_string("recieved data from slave");
	uart_tx(data_rx);
}


