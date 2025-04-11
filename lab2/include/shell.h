#ifndef SHELL_H
#define SHELL_H
#include "mini_uart.h"

#define CMD_NUM 4
#define CMD_SIZE 256

struct command {
	char cmdname[CMD_SIZE];
	char info[CMD_SIZE];
	void (*func)(void);
};

// support cmd
void cmd_help();
void cmd_hello();
void cmd_mailbox();
void cmd_reboot();

void shell();
void read_command(char *str);
void parse_command(char *str);

#endif
