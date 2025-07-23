#include<LPC214X.h>
#include"header.h"

#define RTC_RST (1<<1)
#define RTC_EN 1
#define RTC_32k_SRC (1<<4)

void rtc_init(){
	VPBDIV=0x00;
	PREINT=457;
	PREFRAC=25024;
	CCR = RTC_RST | RTC_32k_SRC;
	SEC=11;
	MIN=54;
	HOUR=12;
	DOM=31;
	DOY=366;
	DOW=0;
	MONTH=12;
	YEAR=2025;
	CCR &= ~RTC_RST;
	CCR |= RTC_EN;
}
int main(){
	unsigned int prev_sec=0xff;
	init_lcd();
	sendcmd(0x80);
	send_string("RTC_Enabled");
	rtc_init();
	while(1){
		if(SEC!=prev_sec){
			prev_sec=SEC;
			sendcmd(0xc0);
			senddata(HOUR/10+48);
			senddata(HOUR%10+48);
			senddata(':');
			senddata(MIN/10+48);
			senddata(MIN%10+48);
			senddata(':');
			senddata(SEC/10+48);
			senddata(SEC%10+48);
		}
	}
}

