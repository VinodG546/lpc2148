#include<LPC214X.h>
#include"header.h"

void delay_ms(int ms){
	T0TC=0;
	T0PR=15000-1;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
}

char keypad_scan() {
    unsigned char row;
    char keys[4][3] = {{'1','2','3'},
                        {'4','5','6'},
                        {'7','8','9'},
                        {'*','0','#'}};

    IODIR0 |= 0x0f;  // Rows as output (P0.0-P0.3)
    IODIR0 &= ~(0x70); // Columns as input (P0.4-P0.6)

    while (1) {
        for (row = 0; row < 4; row++) {
            IOCLR0 = 0x0F;
            IOSET0 = (1 << row);

            if (IOPIN0 & (1 << 4)) return keys[row][0];
            if (IOPIN0 & (1 << 5)) return keys[row][1];
            if (IOPIN0 & (1 << 6)) return keys[row][2];
        }
    }
}


