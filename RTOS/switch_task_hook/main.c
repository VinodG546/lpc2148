#include <LPC214x.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include<string.h>

// Function Prototypes
void LED_Task(void *pvParameters);
void UART_Task(void *pvParameters);
void init_uart(unsigned int baudrate);
void uart_tx(unsigned char data);
void uart_tx_string(const char *str);
void vTaskSwitchedIn(void);

// UART Functions
void init_uart(unsigned int baudrate) {
    PINSEL0 |= 0x05; // Enable UART0 TX and RX
    U0LCR = 0x83;    // Enable DLAB and 8-bit word length
    U0DLL = 98;      // Assuming 15MHz PCLK, for 9600 baudrate
    U0DLM = 0;
    U0LCR = 0x03;    // Disable DLAB
}

void uart_tx(unsigned char data) {
    while (!(U0LSR & 0x20));
    U0THR = data;
}

void uart_tx_string(const char *str) {
    while (*str) {
        uart_tx(*str++);
    }
}

// Hook Function for Task Switch
void vTaskSwitchedIn(void) {
    const char *task = pcTaskGetName(NULL);
    
    // Send to UART
    uart_tx_string("\r\nSwitched In: ");
    uart_tx_string(task);

    // Toggle GPIO pin based on task
    if (strcmp(task, "LED_Task") == 0)
        IOSET0 = (1 << 10); // Set P0.10
    else
        IOCLR0 = (1 << 10); // Clear P0.10
}

// Task 1: Toggle LED
void LED_Task(void *pvParameters) {
    IODIR0 |= (1 << 11); // Set P0.11 as output

    while (1) {
        IOSET0 = (1 << 11); // LED ON
        vTaskDelay(500 / portTICK_PERIOD_MS);
        IOCLR0 = (1 << 11); // LED OFF
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

// Task 2: Send UART Message
void UART_Task(void *pvParameters) {
    while (1) {
        uart_tx_string("\r\nHello from UART_Task");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// Main Function
int main(void) {
    init_uart(9600);
    IODIR0 |= (1 << 10); // P0.10 as output for trace pin

    xTaskCreate(LED_Task, "LED_Task", 128, NULL, 1, NULL);
    xTaskCreate(UART_Task, "UART_Task", 128, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1); // Should never reach here
}

// Required stack overflow hook
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    uart_tx_string("Stack Overflow!\r\n");
    while (1);
}


