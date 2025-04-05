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

// command table
struct command cmd[4] = {
	{.cmdname = "help", .info = "print this help menu", .func = cmd_help},
	{.cmdname = "hello", .info = "print Hello World!", .func = cmd_hello},
	{.cmdname = "mailbox", .info = "print hardware's infomation", .func = cmd_mailbox},
	{.cmdname = "reboot", .info = "reboot the device", .func = cmd_reboot}
};

void shell();
void read_command(char *str);
void parse_command(char *str);

#endif
