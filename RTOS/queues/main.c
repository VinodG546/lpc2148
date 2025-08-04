#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include<stdio.h>


void init_uart(unsigned int baudrate);
void uart_tx(unsigned char data);
void uart_tx_string(char *str);
unsigned char uart_rx(void);

void sender(void *q);
void receiver(void *q);

xQueueHandle myqueue;

int main() {
    init_uart(9600);

    myqueue = xQueueCreate(5, sizeof(unsigned char)); // Queue holds 5 numbers max

    if (myqueue != NULL) {
        xTaskCreate(sender, "Sender", 128, NULL, 1, NULL);
        xTaskCreate(receiver, "Receiver", 128, NULL, 1, NULL);
        vTaskStartScheduler();
    }

    while (1); // Should never reach here
}

// Send numbers from 0 to 255 repeatedly
void sender(void *q) {
    unsigned char num = 0;
    while (1) {
        xQueueSendToBack(myqueue, &num, portMAX_DELAY);
        num++;
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay to make it observable
    }
}

// Receive and print number
void receiver(void *q) {
    unsigned char receivedValue;
    char buffer[10];
    while (1) {
        if (xQueueReceive(myqueue, &receivedValue, portMAX_DELAY) == pdPASS) {
            sprintf(buffer, "%d\r\n", receivedValue);
            uart_tx_string(buffer);
        }
    }
}

// Required stack overflow hook
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    uart_tx_string("Stack Overflow!\r\n");
    while (1);
}
