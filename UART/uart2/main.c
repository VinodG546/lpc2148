#include<LPC21XX.h>
#include"header.h"

#define led1 5
#define led2 6

unsigned char mydata;
int main(){
	IODIR0 |= (1<<led1) | (1<<led2);  // Set P0.5 and P0.6 as output

	init_uart(9600);
	while(1){
		uart_tx_string("my name is vinod");
		mydata=uart_rx();
		if(mydata=='A'){
			IOSET0|=1<<led1;
			IOCLR0|=1<<led2;
		}
		else if(mydata=='B'){
			IOSET0|=1<<led2;
			IOCLR0|=1<<led1;
		}
	}
}

	

