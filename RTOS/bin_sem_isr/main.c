#include<stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void init_uart(unsigned int baud);
void uart_tx(unsigned char data);
void uart_tx_string(const char *str);
unsigned char uart_rx(void);
void rx1(void)__irq;

void initpll(void);
void recsemaphore(void *q);

xSemaphoreHandle bin_sem;
int main(){
	vSemaphoreCreateBinary(bin_sem);
	init_uart(9600);
	initpll();
	xSemaphoreTake(bin_sem,portMAX_DELAY);
	xTaskCreate(recsemaphore,"intertask",128,NULL,1,NULL);
	vTaskStartScheduler();
	while(1);
}
void recsemaphore(void *q)
{
  while(1) {
    if(xSemaphoreTake(bin_sem,portMAX_DELAY)==pdTRUE) {
      uart_tx_string("Received Semaphore From ISR");
      uart_tx_string("\r\n");
      uart_tx_string("\r\n");
    }
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

void rx1(void)__irq
{
  unsigned char r;
  static portBASE_TYPE interrupttask;
  interrupttask=pdFALSE;
  
  if(U0IIR&0x04) {
    r=U0RBR;
    uart_tx_string("Received Data : ");
    U0THR=r;
    while(!(U0LSR&0x20));
    uart_tx_string("\r\n");
    uart_tx_string("Going to give semaphore");
    uart_tx_string("\r\n");
    xSemaphoreGiveFromISR(bin_sem,&interrupttask);
    uart_tx_string("Semaphore has given");
    uart_tx_string("\r\n");
  }
  VICVectAddr = 0x00;
}

