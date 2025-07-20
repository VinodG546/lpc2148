#include<LPC214X.H>
#include"header.h"
#define FACTOR 10.23 

int main(){
	//unsigned int data=0 ;
	dac_init();
	
	///Genarate SAWTOOTH wave 
	while(1){
		/*dac_write(data); //Writting digital data to genarate analog output 
		delay_us(200);//delay to produce samples
		data+=FACTOR; 
		
		if(data > 1023 ){
			data=0;
		}*/
		int i;
		for(i=0;i<50;i++){
			dac_write(i*20);
			delay_us(200);
		}
		for(i=0;i<50;i++){
			dac_write(1000-(i*20));
			delay_us(200);
		}
	}
}

