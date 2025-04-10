#include "shell.h"
#include "mini_uart.h"

int main() {
	uart_init();
	shell();
	return 0;
}
