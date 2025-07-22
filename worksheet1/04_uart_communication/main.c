#include<LPC214X.h>
#include"header.h"
#include"timer.h"
#define led 1<<5
int main(){
	int cnt=0;
	IO0DIR |= led;
	uart_init(9600);
	while(1){
		IO0SET|=led;
		cnt++;
		uart_tx_string("led count:");
		uart_tx(cnt+48);
		uart_tx_string("\r\n");
		delay_ms(1000);
		IO0CLR|=led;
		delay_ms(1000);
	}
}


