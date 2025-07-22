#include<LPC214X.h>
#include"header.h"
#include"timer.h"

#define sw ((IO0PIN>>15)&1)
int main(){
	int cnt=0,flag=0;
	uart_init(9600);
	uart_tx_string("push_button");
	while(1)
	{
		if(sw==0&&flag==0)
		{
			cnt++;
			uart_tx_string("no of times button pressed:");
			uart_tx(cnt+'0');
			uart_tx_string("\r\n");
			flag=1;
			delay_ms(100);
		}
		else if(sw==1){
			flag=0;
		}
	}
}


