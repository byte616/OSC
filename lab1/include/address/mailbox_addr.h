#ifndef MAILBOX_ADDR_H
#define MAILBOX_ADDR_H

#include "base_addr.h"

#define MAILBOX_READ     ((volatile unsigned int*)(MAILBOX_BASE+0x00))
#define MAILBOX_STATUS   ((volatile unsigned int*)(MAILBOX_BASE+0x18))
#define MAILBOX_WRITE    ((volatile unsigned int*)(MAILBOX_BASE+0x20))


#define MAILBOX_EMPTY    0x40000000
#define MAILBOX_FULL     0x80000000


#define GET_BOARD_REVISION  0x00010002
#define GET_ARM_MEMORY      0x00010005
#define REQUEST_CODE        0x00000000
#define REQUEST_SUCCEED     0x80000000
#define REQUEST_FAILED      0x80000001
#define TAG_REQUEST_CODE    0x00000000
#define END_TAG             0x00000000

#endif
