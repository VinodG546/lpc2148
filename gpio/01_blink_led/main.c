#include<lpc21xx.h>
void delay(void);

const int ledpin=0;//GPIO p0.5 as ledpin 

int main(){
	IODIR0|=1<<ledpin;//making ledpin as ouput
	while(1){
		IOSET0 |= 1<<ledpin;//setting ledpin to ON the led
		delay();            // giving some delay
		IOCLR0|= 1<<ledpin; //Clearing the ledpin for toggling the led
		delay();						//some delay
		}
}
//code for delay
void delay(void){
	int i;
	for(i=0;i<1000000;i++);
}



