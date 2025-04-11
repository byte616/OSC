#ifndef MAILBOX_H
#define MAILBOX_H

#include "address/mailbox_addr.h"

void get_board_revision();
void get_arm_baseaddr();
int mailbox_call();

#endif
