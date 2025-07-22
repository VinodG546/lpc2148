#include<LPC214X.h>
#include"header.h"
#include"timer.h"

int main(){
	char data_tx;
	spi_init();
	uart_init(9600);
	
	uart_tx_string("spi_slave");
	
	data_tx=spi_read();
	
	uart_tx_string("recieved data from master");
	uart_tx(data_tx);
	
	spi_write('B');
}

