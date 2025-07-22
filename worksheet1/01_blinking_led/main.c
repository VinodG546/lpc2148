#include<LPC214X.h>
#include"timer.h"
#include"header.h"

#define led1 1<<0
#define led2 1<<1


int main(){
	IO0DIR |= led1 | led2;
	while(1){
		IO0SET |= led1;
		IO0CLR |= led2;
		delay_ms(1000);
		IO0SET |= led2;
		IO0CLR |= led1;
		delay_ms(500);
	}
}

