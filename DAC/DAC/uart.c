#include<LPC214X.H>
#include "header.h"

//status flags of uart0 
#define THRE ((U0LSR>>5)&1 )
#define RDR (U0LSR&1) 


/*
Uart intialization  function 
*/

void uart_init(unsigned int baud ){
	int result;
	int a[]={1 , 4 , 2 ,1};
	unsigned int pclk=a[VPBDIV&0x3]*15000000; //Getting pclk from VPBDIV setting 
	
	//configuring pin functionallity 
	PINSEL0|=0X5;
	result=(pclk/(baud*16));
	
	//Enabling  DLAB bit to configure baud rate 
	U0LCR=0X83;
	
	//Assing buad value to lower byte and higher byte 
	U0DLL=(result&0xff);    
	U0DLM=((result>>8)&0xff);
	
	//Disabling DLAB bit  
	U0LCR=0X3;
	
}

/*void uart_init(unsigned int baud ){
	PINSEL0=0x5;
	U0LCR=0X83;
	U0DLL=97;
	U0LCR=0X3;
	
}
*/

void uart_tx(unsigned char data ){
	U0THR=data; // Assinging data to transmit buffer	
	while(THRE == 0);
}

void uart_tx_string(const char *message ){
	int i;
	for ( i=0; message[i] ;i++){
		uart_tx(message[i]);
	}
}

unsigned char uart_rx(void ){
	unsigned char data;
	while(RDR == 0);
	
	data=U0RBR; //Assining  recived data from buffer to local variable
	return data ;
}



///Function to print interger

void uart_tx_int(unsigned int num){
	int k=1000;
	
	while(num/10){
		uart_tx((num/k)+'0');
		num=num%k;
		k/=10;
	}
	uart_tx(num+'0');
}


