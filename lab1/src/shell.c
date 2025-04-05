#include "shell.h"
#include "utils.h"

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];

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

// TODO
void cmd_mailbox() {

}

// TODO
void cmd_reboot() {
	uart_sendstr("Rebooting...\n");
	*PM_WDOG = PM_PASSWORD | 600; // set tick
	*PM_RSTC = PM_PASSWORD | PM_RSTC_FULLRST; // reboot
	while (1); // wait for reboot, do not execute other inst.
}

void read_command(char *str) {
	int idx = 0;
	while(idx < BUFFER_SIZE) {
		buffer[idx] = uart_recv();
		uart_send(buffer[idx]);
		if(buffer[idx] == '\n') {
			buffer[idx] = '\0';
			break;
		}
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
