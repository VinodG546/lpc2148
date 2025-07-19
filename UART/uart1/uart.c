#include<LPC21XX.h>
#include"header.h"

#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)

void init_uart(unsigned int baud){
	int result;
	int a[]={1,4,2,1};
	//getting pclk from vpbdiv
	unsigned int pclk=a[VPBDIV&0x03]*15000000;
	
	//configuring gpio pins 0.0 and 0.1
	PINSEL0|=0x05;
	//divisor
	result=(pclk/(baud*16));
	//enabling DLAB bit for baud rate
	U0LCR=0x83;
	//assigning baud value to lsb and msb bit 
	U0DLL=(result&0xff);
	U0DLM=((result>>8)&0xff);
	//disabling DLAB bit
	U0LCR=0x3;
}

void uart_tx(unsigned char data){
	U0THR=data;
	while(THRE==0);
}

void uart_tx_string(const char *str){
	int i;
	for(i=0;str[i];i++){
		uart_tx(str[i]);
	}
}

unsigned char uart_rx(void){
	unsigned char data;
	while(RDR==0);
	data=U0RBR;
	return data;
}
	
	
