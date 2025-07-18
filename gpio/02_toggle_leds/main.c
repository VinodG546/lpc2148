#include<lpc214X.h>
const int ledpin1 = 5;
const int ledpin2 = 10;
void delay()
{
	int i;
	for(i=0;i<2000000;i++);
}
int main(){
	IODIR0 |= 1<<5 | 1<<10; //made ledpin1 and ledpin2 GPIOs as outputs
	while(1){
		IOSET0 |= 1<<ledpin1;
		delay();
		IOCLR0 |= 1<<ledpin1;
		IOSET0 |= 1<<ledpin2;
		delay();
		IOCLR0 |= 1<<ledpin2;
	}
}

