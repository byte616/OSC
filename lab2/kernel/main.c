#include "shell.h"
#include "mini_uart.h"

int main() {
	uart_init();
	uart_sendstr("enter OS successfully\n");
	shell();
	return 0;
}
