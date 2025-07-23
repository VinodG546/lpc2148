#include <LPC214x.h>
#include "header.h"  // LCD functions like init_lcd, sendcmd, senddata, send_string, etc.
#include <stdio.h>



void init_rtc() {
    CCR = 0x02; // Reset Clock
    SEC = 0; MIN = 59; HOUR = 11; // Set initial time 11:59:00
    CCR = 0x01; // Enable RTC
}

int main() {
    char time_str[17];

    init_lcd();
    sendcmd(0x80);
    send_string("Time:");

    init_rtc();

    while (1) {
        // Format time as HH:MM:SS
        sprintf(time_str, "%02d:%02d:%02d", HOUR, MIN, SEC);
        sendcmd(0x86); // Move to column 6 (after "Time:")
        send_string(time_str);
        delay_ms(1000); // Update every 1 second
    }
}
