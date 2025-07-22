#include<LPC214X.h>
#include"header.h"
#include"timer.h"

int main(){
	int adc_val;
	float val;
	char str[]="temp:";
	char *ptr=str;
	adc_init();
	init_lcd();
	
	while(1){
		adc_val=adc_read();
		val=adc_to_temp(adc_val);
		sendcmd(0x83);
		while(*ptr!='\0'){
			senddata(*ptr++);
		}
		sendcmd(0x88);
		floatlcd(val,2);
		delay_ms(100);
		
	}
}

