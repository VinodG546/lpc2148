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
	SEC=59;
	MIN=59;
	HOUR=23;
	DOM=31;
	DOY=366;
	DOW=0;
	MONTH=12;
	YEAR=2025;
	CCR &= ~RTC_RST;
	CCR |= RTC_EN;
}
int main(){
	