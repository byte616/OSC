#include "mailbox.h"
#include "mini_uart.h"
#include "utils.h"

#define CHANNEL8 0x8
volatile unsigned int mailbox[36] __attribute__((aligned(16)));

void get_board_revision() {
	
	mailbox[0] = 7 * 4;              // buffer size in bytes
	mailbox[1] = REQUEST_CODE;
	mailbox[2] = GET_BOARD_REVISION; // tags begin (tag identifier)
	mailbox[3] = 4;                  // maximum response value buffer's length
	mailbox[4] = TAG_REQUEST_CODE;
	mailbox[5] = 0;                  // value buffer
	mailbox[6] = END_TAG;            // tags end

	// message passing procedure call
	mailbox_call(mailbox); 
	
	// output
	char output[128];
	uint2hexstr(output, mailbox[5]);
	uart_sendstr("Board revision: ");
	uart_sendstr(output);
}

void get_arm_baseaddr() {
	
	mailbox[0] = 8 * 4;
	mailbox[1] = REQUEST_CODE;
	mailbox[2] = GET_ARM_MEMORY;
	mailbox[3] = 8;
	mailbox[4] = TAG_REQUEST_CODE;
	mailbox[5] = 0;
	mailbox[6] = 0;
	mailbox[7] = END_TAG;

	
	// message passing procedure call
	mailbox_call(mailbox); 

	// output
	char output[128];
	uart_sendstr("Arm memory base address: ");
	uint2hexstr(output, mailbox[5]);
	uart_sendstr(output);

	uart_sendstr("Arm memory size: ");
	uint2hexstr(output, mailbox[6]);
	uart_sendstr(output);
}

int mailbox_call() {
	unsigned int msg_phys = (unsigned int)(unsigned long) mailbox;
	// upper 28  bits --> message address, lower 28 bits --> channel num
	unsigned int value = (msg_phys & ~0xF) | (CHANNEL8 & 0xF);

	// check mailbox is full or not, if full, we can not write
	while (*MAILBOX_STATUS & MAILBOX_FULL); 
	*MAILBOX_WRITE =  value;

	// check mailbox is empty or not, if empty, GPU does not response yet
	while (*MAILBOX_STATUS & MAILBOX_EMPTY); 
	unsigned int read = *MAILBOX_READ;

	// check address right or not
	if(read == value) {
		return mailbox[1] == REQUEST_SUCCEED;
	}
	return 0;
}
