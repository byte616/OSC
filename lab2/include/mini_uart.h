#ifndef MINI_UART_H
#define MINI_UART_H
#include "address/uart_addr.h"
#include "address/gpio_addr.h"

void uart_init();
char uart_recv();
unsigned int uart_recv4();
void uart_send(char c);
void uart_sendstr(const char *str);

#endif
