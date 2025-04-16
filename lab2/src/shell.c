#include "shell.h"
#include "utils.h"
#include "mailbox.h"

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];

// command table
struct command cmd[4] = {
	{.cmdname = "help", .info = "print this help menu", .func = cmd_help},
	{.cmdname = "hello", .info = "print Hello World!", .func = cmd_hello},
	{.cmdname = "mailbox", .info = "print hardware's infomation", .func = cmd_mailbox},
	{.cmdname = "reboot", .info = "reboot the device", .func = cmd_reboot}
};


//  support cmd
void cmd_help() {
	for(int i = 0; i < CMD_NUM; i++) {
		uart_sendstr(cmd[i].cmdname);
		uart_sendstr("\t: ");
		uart_sendstr(cmd[i].info);
		uart_sendstr("\n");
	}
}

void cmd_hello() {
	uart_sendstr("Hello World!\n");
}

void cmd_mailbox() {
	uart_sendstr("Mailbox info:\n");
	get_board_revision();		
	get_arm_baseaddr();
}

void cmd_reboot() {
	uart_sendstr("Rebooting...\n");
	reset(1200);
	while(1);
}

void read_command(char *str) {
	int idx = 0;
	while(idx < BUFFER_SIZE) {
		buffer[idx] = uart_recv();
		if(buffer[idx] == '\n') {
			uart_sendstr("\n"); // sendstr will add '\r'
			buffer[idx] = '\0';
			break;
		}
		uart_send(buffer[idx]);
		idx += 1;
	}
}

void parse_command(char *str) {
	for(int i = 0; i < CMD_NUM; i++) {
		if(strcmp(str, cmd[i].cmdname) == 0) {
			cmd[i].func();
			return;
		}
	}
	uart_sendstr("Command not found: ");
	uart_sendstr(str);
	uart_sendstr("\n");
}

void run_welcome() {
	uart_sendstr("Welcome to my OS\n");
}

void shell() {
	run_welcome();
	while(1) {
		uart_sendstr("# ");
		read_command(buffer);
		parse_command(buffer);
	}
}
