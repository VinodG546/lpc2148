#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void initpll(void);
void task1(void *p);
void task2(void *p);

void init_uart(unsigned int baud);
void uart_tx(unsigned char data);
void uart_tx_string(const char *str);
unsigned char uart_rx(void);
//extern void rx1(void);  // Add this line in uart.c

xSemaphoreHandle countingsemaphore;

int main()
{
	initpll();
  init_uart(9600);
  countingsemaphore=xSemaphoreCreateCounting(3,0);
  xTaskCreate(task1,"task1",128,NULL,1,NULL);
  xTaskCreate(task2,"task2",128,NULL,1,NULL);
  vTaskStartScheduler();
  while(1);
  
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
void task1(void *p)
{
  while(1) {
    if(countingsemaphore!=NULL) {      
      if(xSemaphoreTake(countingsemaphore,portMAX_DELAY)==pdTRUE) {
        uart_tx_string("Task 1 Takes Semaphore");
        uart_tx_string("\r\n");
        uart_tx_string("\r\n");
      }
    }
  }
}
void task2(void *p)
{
  while(1) {
    if(countingsemaphore!=NULL) {      
      if(xSemaphoreTake(countingsemaphore,portMAX_DELAY )==pdTRUE) {
        uart_tx_string("Task 2 Takes Semaphore");
        uart_tx_string("\r\n");
        uart_tx_string("\r\n");
      }
    }
  }
}
void rx1(void)__irq
{
  static portBASE_TYPE interrupttask;
  unsigned char r;
  
  if(U0IIR&0x04) {
    r=U0RBR;
    uart_tx_string("Received Data = ");
    U0THR=r;
    while(!(U0LSR&0x20));
    uart_tx_string("\r\n");
    uart_tx_string("Going to Give Semaphore From ISR");
    uart_tx_string("\r\n");
    xSemaphoreGiveFromISR(countingsemaphore,&interrupttask );    
  }
  VICVectAddr = 0x00;
  
}