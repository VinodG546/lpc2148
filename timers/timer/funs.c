#include<LPC21XX.h>

void delayms(int ms){
	T0TC=0; //resets time
	T0PR=15000-1; //ptr+1 value pclk/tclk
	T0TCR=0X01; //enable timer
	while(T0TC < ms);//loop in until totc == ms
	T0TCR=0X00; //disable timer
}

void delayus(int us){
	T0TC=0; //resets time
	T0PR=15-1; //ptr+1 value pclk/tclk
	T0TCR=0X01; //enable timer
	while(T0TC < us);//loop in until totc == ms
	T0TCR=0X00; //disable timer
}
/*
void init_pll(){
	PLL0CON=0X01;//enable the first pin 
	PLL0CFG=0X24; //MSEL and PSEL =0x24
	PLL0FEED=0XAA;//pin
	PLL0FEED=0X55;//pin
	while(((PLL0STAT>>10)&1)==0);//waits until lock bit sets
	PLL0CON=0X03;//ENABLE and connect pll
	PLL0FEED=0XAA;
	PLL0FEED=0X55;
	VPBDIV=0X04;
}*/
