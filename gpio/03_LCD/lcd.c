#include<LPC21xx.h>

#include "header.h"

#define RS 1<<16
#define RW 1<<17
#define EN 1<<18

void delay(){
	int i=0;
	for(;i<2000000;i++);
}
void init_lcd(){
	IODIR1 |= RS | RW | EN | 0xff000000;
	sendcmd(0x38);//function set : 8bit , 2lines ,5*7 dots
	delay();
	sendcmd(0x0E);//display ON,cursor ON
	delay();
	sendcmd(0x06);//entry mode - increment cursor
	delay();
	sendcmd(0x01);//clear display screen
	delay();
	sendcmd(0x83);//second row fourth character pos
	delay();
}

void sendcmd(unsigned int cmd){
	IOCLR1=RS;//pull down the RS pin for command
	IOCLR1=RW;//pull down the RW pin to write
	
	IOCLR1=0xff000000;
	IOSET1=(cmd & 0xff) << 24;
	
	IOSET1=EN;
	delay();
	IOCLR1=EN;
}

void senddata(unsigned char data){
	IOSET1=RS;
	IOCLR1=RW;
	
	IOCLR1=0xff000000;
	IOSET1=(data & 0xff)<<24;
	
	IOSET1=EN;
	delay();
	IOCLR1=EN;
}

	
