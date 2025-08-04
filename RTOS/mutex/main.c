#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

void init_uart(unsigned int baud);
void uart_tx(unsigned char data);
void uart_tx_string(const char *str);
unsigned char uart_rx(void);

void initpll(void);
void task1(void *p);
void task2(void *p);
xSemaphoreHandle xMutex=NULL;

int main(){
	initpll();
	init_uart(9600);
	xMutex=xSemaphoreCreateMutex();
	if(xMutex != NULL){
		xTaskCreate(task1,"task1",256,NULL,1,NULL);
		xTaskCreate(task2,"task2",256,NULL,1,NULL);
    vTaskStartScheduler();
  }
  while(1);
}
void task1(void *p)
{
  while(1) {
    xSemaphoreTake(xMutex,portMAX_DELAY );
    uart_tx_string("Task1 functioning");
    uart_tx_string("\r\n");
    xSemaphoreGive( xMutex );
    vTaskDelay(5);
  }
}
void task2(void *p)
{
  while(1)
  {
    xSemaphoreTake(xMutex,portMAX_DELAY );
    uart_tx_string("Task2 functioning");
    uart_tx_string("\r\n");
    xSemaphoreGive(xMutex);
    vTaskDelay(5);
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
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName){
    uart_tx_string("STACK OVERFLOW\r\n");
    while(1);
}

