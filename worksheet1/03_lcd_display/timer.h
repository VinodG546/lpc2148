#include<LPC214X.h>
#include"header.h"

void delay_ms(int ms){
	T0TC=0; //resets time
	T0PR=15000-1; //ptr+1 value pclk/tclk
	T0TCR=0X01; //enable timer
	while(T0TC < ms);//loop in until totc == ms
	T0TCR=0X00; //disable timer
}

void delay_us(int us){
	T0TC=0; //resets time
	T0PR=15-1; //ptr+1 value pclk/tclk
	T0TCR=0X01; //enable timer
	while(T0TC < us);//loop in until totc == ms
	T0TCR=0X00; //disable timer
}
