#include "mini_uart.h"

void wait(unsigned int time) {
	while(time--) {
		// asm --> inline assembly
		// volatile tell compiler not to optimize nop
		asm volatile("nop");
	}
}

void uart_init() {
	// set GPFSEL1 12~14 bit(GPIO14) & 15~17 bit(GPIO15) to 010(ALT5)
	unsigned int tmp;
	tmp = *GPFSEL1;
	tmp &= ~(7u << 12); // 111 move 12 bit, and use '~' to convert 0 & 1, clean GPIO14
	tmp |= 2u << 12; // 2u = 010(ALT5)
	tmp &= ~(7u << 15); // clean GPIO15
	tmp |= 2u << 15;
	*GPFSEL1 = tmp;

	// disable basic I/O
	*GPPUD = 0;
	wait(150u);
	*GPPUDCLK0 = (1u << 14) | (1u << 15); // select GPIO 14, 15 to set
	wait(150u);
	*GPPUDCLK0 = 0u; // clear

	// initialization
	*AUX_ENABLES = 1u;
    *AUX_MU_CNTL_REG = 0u;
    *AUX_MU_IER_REG = 0u;
    *AUX_MU_LCR_REG = 3u;
    *AUX_MU_MCR_REG = 0u;
    *AUX_MU_BAUD_REG = 270u;
    *AUX_MU_IIR_REG = 6u;
    *AUX_MU_CNTL_REG = 3u;
}

char uart_recv() {
	// check bit0 == 1, if yes, read it; otherwise, wait
	while(!(*AUX_MU_LSR_REG & 0x01));
	char c = (char)(*AUX_MU_IO_REG);
	return c == '\r' ? '\n' : c;
}

void uart_send(char c) {
	// check bit 5 == 1, if yes, write it; otherwise, wait
	// 0x20 = 0010 0000
	while(!(*AUX_MU_LSR_REG & 0x20));
	*AUX_MU_IO_REG = c;
}

void uart_sendstr(const char *str) {
	while(*str) {
		if(*str == '\n') uart_send('\r');
		uart_send(*str++);
	}
}

unsigned int uart_recv4() {
	char buffer[4];
	for(int i = 0; i < 4; i++) {
		buffer[i] = uart_recv();
	}
	return *((unsigned int*) buffer);
}

// interrupt todo
// 1. enable TX/RX interrupt, 2. check cause
