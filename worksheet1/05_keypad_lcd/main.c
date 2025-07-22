#include <LPC214x.h>
#include "header.h"
#include <string.h>

int main() {
    char key;
    char *password = "1234";
    char sendpass[5];  // Buffer to hold 4 digits + null terminator
    int i = 0;

    init_lcd();
    sendcmd(0x83);  // Cursor to 1st row, 3rd column

    while (1) {
        while (i < 4) {
            key = keypad_scan(); 
						delay_ms(50);					// Read key
            if (key != '\0') {       // Print only if valid key pressed
                senddata(key);
                sendpass[i] = key;
                i++;
                delay_ms(30);       // Debounce delay
            }
        }
        sendpass[i] = '\0';  // Null-terminate the string

        if (strcmp(sendpass, password) == 0) {
            sendcmd(0xC0);  // Move to 2nd row, 3rd column
            send_string("Vault Open");
        } else {
            sendcmd(0xC0);
            send_string("Wrong Pass");
        }

        delay_ms(2000);  // Wait before clearing
        sendcmd(0x01);   // Clear LCD
        sendcmd(0x80);   // Reset cursor
        i = 0;           // Reset counter
    }
}
