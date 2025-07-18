#include"header.h"

int i;
int main(){
	unsigned char str1[]="HELLO WORLD";
	unsigned char str2[]="LCD";
	init_lcd();
	sendcmd(0x83);
	for(i=0;i<12;i++){
		senddata(str1[i]);
	}
	sendcmd(0xc7);
	for(i=0;i<3;i++){
		senddata(str2[i]);
	}
	sendcmd(0x0c);
	while(1);
}
	

