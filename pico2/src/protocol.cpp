#include "protocol.h"
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

#define UART_ID uart0
#define BUFFER_SIZE 128

static char command_buffer[BUFFER_SIZE];
static int buffer_index = 0;

void protocol_init() {
    printf("[Protocol] Initialized\n");
}

void protocol_handle_char(char c) {
    if (c == '\n' || c == '\r') {
        if (buffer_index > 0) {
            command_buffer[buffer_index] = '\0';
            protocol_process_command(command_buffer);
            buffer_index = 0;
        }
    } else if (buffer_index < BUFFER_SIZE - 1) {
        command_buffer[buffer_index++] = c;
    }
}

void protocol_process_command(const char* command) {
    printf("[Protocol] Received: %s\n", command);

    if (strncmp(command, "PING", 4) == 0) {
        uart_puts(UART_ID, "OK PING\n");
        printf("[Protocol] PING response sent\n");
    } else if (strncmp(command, "STATUS", 6) == 0) {
        uart_puts(UART_ID, "OK STATUS RUNNING\n");
        printf("[Protocol] STATUS response sent\n");
    } else if (strncmp(command, "GPIO", 4) == 0) {
        // GPIO pin value
        printf("[Protocol] GPIO command received\n");
        uart_puts(UART_ID, "OK GPIO\n");
    } else {
        uart_puts(UART_ID, "ERROR UNKNOWN\n");
        printf("[Protocol] Unknown command\n");
    }
}
