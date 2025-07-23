#include <LPC214x.h>
#include"header.h"
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 6000; j++);
}

void init_pwm6() {
    // Set P0.9 as PWM6 output
    PINSEL0 |= (1 << 18);    // Bit 18 = 1
    PINSEL0 &= ~(1 << 19);   // Bit 19 = 0 ? P0.9 as PWM6

    PWMPCR = (1 << 14);      // Enable PWM6 output
    PWMPR = 15 - 1;          // Prescaler: 15MHz / 15 = 1 MHz
    PWMMR0 = 10000;          // PWM Period = 10ms (100 Hz)
    PWMMR6 = 5000;           // 50% duty cycle

    PWMMCR = (1 << 1);       // Reset PWMTC on match with MR0
    PWMLER = (1 << 0) | (1 << 6); // Enable latch for MR0 and MR6

    PWMTCR = (1 << 1);       // Reset Timer Counter
    PWMTCR = (1 << 0) | (1 << 3); // Enable counter and PWM mode
}

int main() {
    // Set IN3 = 1, IN4 = 0 for forward
		uart_init(9600);
    IODIR0 |= (1 << 22) | (1 << 23); // P0.22, P0.23 output
    IOSET0 |= (1 << 22);             // IN3 = 1
    IOCLR0 |= (1 << 23);             // IN4 = 0
		uart_tx_string("pwm works at duuty cycle:50%");
    init_pwm6(); // Start PWM6 on P0.9 with 50% duty
		
    while (1) {
        // Motor runs at 50% speed
    }
}
