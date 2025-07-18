#include"timer.h"
#include<LPC21XX.h>
#define led 1<<15
int main(){
	//init_pll();
	while(1){
		IODIR0=led;
		IOSET0=led;
		delayms(100);
		IOCLR0=led;
		delayms(100);
	}
}
