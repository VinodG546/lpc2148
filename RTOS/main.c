#include <lpc214x.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "header.h"


void task1(void *q);
void task2(void *a);
void initpll(void);
int main(void)
{
  initpll();
  init_uart(9600);
	//uart_tx('a');
  xTaskCreate(task1, "task1", 128, NULL, 1, NULL);
	xTaskCreate(task2, "task1", 128, NULL, 1, NULL); 
  vTaskStartScheduler();
	
}
void task1(void *q)
{  
  while(1) {  
    uart_tx_string("Task1 functioning");
    uart_tx_string("\r\n");
    vTaskDelay(1);

  }
}
void task2(void *a)
{
  while(1) {
		
    uart_tx_string("Task2 functioning");
    uart_tx_string("\r\n");
		vTaskDelay(1);
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
