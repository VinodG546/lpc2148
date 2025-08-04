#include <LPC214X.h>
#include "FreeRTOS.h"
#include"task.h"
//#include "header.h"

void print(void *q);
void initpll(void);
void init_uart(unsigned int baud);
void uart_tx(unsigned char data);
void uart_tx_string(const char *str);
unsigned char uart_rx(void);



int main(){
	init_uart(9600);
	initpll();
	xTaskCreate(print,"print1",128,"task 1 functioning",1,NULL);
	xTaskCreate(print,"print2",128,"task 2 functioning",1,NULL);
	vTaskStartScheduler();
}
void print(void *q){
	const char *p;
	while(1){
		p=(const char *)q;
		uart_tx_string(p);
		uart_tx_string("\r\n");
		vTaskDelay(1000);
	}
}
void initpll(void)
{
  PLL0CON=0x01;
  PLL0CFG=0x24;
  PLL0FEED=0xAA;
  PLL0FEED=0x55;
  while(!(PLL0STAT&1<<10));
  PLL0CON=0x03;
  PLL0FEED=0xAA;
  PLL0FEED=0x55;
  VPBDIV=0x01;
}

