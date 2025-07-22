#include<LPC21xx.h>

#include "header.h"

#define RS 1<<16
#define RW 1<<17
#define EN 1<<18

void init_lcd(){
	IODIR1 |= RS | RW | EN | 0xff000000;
	sendcmd(0x38);//function set : 8bit , 2lines ,5*7 dots
	delay_ms(100);
	sendcmd(0x0E);//display ON,cursor ON
	delay_ms(100);
	sendcmd(0x06);//entry mode - increment cursor
	delay_ms(100);
	sendcmd(0x01);//clear display screen
	delay_ms(100);
	sendcmd(0x83);//second row fourth character pos
	delay_ms(100);
}

void sendcmd(unsigned int cmd){
	IOCLR1=RS;//pull down the RS pin for command
	IOCLR1=RW;//pull down the RW pin to write
	
	IOCLR1=0xff000000;
	IOSET1=(cmd & 0xff) << 24;
	
	IOSET1=EN;
	delay_ms(100);
	IOCLR1=EN;
}

void senddata(unsigned char data){
	IOSET1=RS;
	IOCLR1=RW;
	
	IOCLR1=0xff000000;
	IOSET1=(data & 0xff)<<24;
	
	IOSET1=EN;
	delay_ms(100);
	IOCLR1=EN;
}
void floatlcd(float num, int decimal_places) {
    int int_part = (int)num;
    int frac_part;
    int i;

    if (num < 0) {
        senddata('-');
        num = -num;
        int_part = (int)num;
    }

    // Print integer part
    if (int_part == 0) {
        senddata('0');
    } else {
        char int_str[10];
        int i = 0;
        while (int_part > 0) {
            int_str[i++] = (int_part % 10) + '0';
            int_part /= 10;
        }
        // Print in reverse
        while (i--) {
            senddata(int_str[i]);
        }
    }

    senddata('.');

    // Print fractional part
    num = num - (int)num;
    for (i = 0; i < decimal_places; i++) {
        num *= 10;
        frac_part = (int)num;
        senddata(frac_part + '0');
        num -= frac_part;
    }
}
