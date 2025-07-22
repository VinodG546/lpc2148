#include <LPC214x.h>
#include"header.h"

#define LED (1<<10)

void led_init(void) {
    IODIR0 |= LED;     // Set P0.10 as output
}

void led_on(void) {
    IOSET0 = LED;
}

void led_off(void) {
    IOCLR0 = LED;
}

void i2c_slave_init(void) {
    PINSEL0 |= (1 << 4) | (1 << 6); // P0.2 = SCL, P0.3 = SDA
    I2C0CONCLR = 0x6C;              // Clear STA, STO, SI, AA
    I2C0SCLH = 0x32;
    I2C0SCLL = 0x32;
    I2C0ADR = 0x50 << 1;            // Set slave address (upper 7 bits only)
    I2C0CONSET = 0x44;              // Enable I2C (I2EN) + Assert ACK (AA)
}

int main(void) {
    unsigned char data;
    
    led_init();
    i2c_slave_init();
		uart_init(9600);
	  uart_tx_string("i2c slave intialised");
    while (1) {
			  uart_tx('\n');
        if (I2C0CONSET & 0x08) { // SI is set (I2C event occurred)
            switch (I2C0STAT) {

                case 0x60:  // SLA+W received, ACK returned
                case 0x68:  // Arbitration lost, SLA+W received, ACK returned
                    I2C0CONCLR = 0x08;  // Clear SI
                    break;

                case 0x80:  // Data received, ACK returned
                    data = I2C0DAT;     // Read received data
                    if (data == 'A')
										{
												uart_tx('A');
                        led_on();
										}
                    else
                        led_off();
                    I2C0CONCLR = 0x08;  // Clear SI
                    break;

                case 0x88:  // Data received, NACK returned
                    I2C0CONCLR = 0x08;
                    break;

                case 0xA0:  // STOP or repeated START received
                    I2C0CONCLR = 0x08;  // Clear SI
                    break;

                default:
                    I2C0CONCLR = 0x08;  // Clear SI for all other states
                    break;
            }
        }
    }
}
