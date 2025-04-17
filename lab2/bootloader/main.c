#include "mini_uart.h"
#include "utils.h"
#include "shell.h"

void load_img() {
	// receive kernel size
	uart_sendstr("waiting for header...\n");
	unsigned int kernel_size = uart_recv4();
	
	// output kernel size
	char output[64];
	to_string(output, kernel_size);
	uart_sendstr("kernel size: ");
	uart_sendstr(output);
	uart_sendstr("\n");

	// write kerenl data into 0x80000
	char *kernel_data = (char*)(KERNEL_LOAD);
	for(unsigned int i = 0; i < kernel_size; i++) {
		kernel_data[i] = uart_recv();
	}
	uart_sendstr("kernel loaded finished : )\n");

	// jump to kernel 
	void (*kernel_entry)(void) = (void *)0x80000;
}

int main() {
	uart_init();
	uart_sendstr("booting...\n");
	load_img();
	return 0;
}
