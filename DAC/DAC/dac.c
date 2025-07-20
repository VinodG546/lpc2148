#include<LPC214X.h>
#include"header.h"
void dac_init(void){
	PINSEL1 |= 0x00004;
}
void dac_write(unsigned int digital_data)
{
	DACR = (digital_data&0x3ff)<<6;
}
	




