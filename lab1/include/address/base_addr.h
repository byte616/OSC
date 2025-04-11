#ifndef BASE_ADDR_H
#define BASE_ADDR_H

#define MMIO_BASE     0x3F000000
#define MAILBOX_BASE  MMIO_BASE + 0xb880

// reboot
#define PM_RSTC         ((volatile unsigned int*)(MMIO_BASE + 0x0010001C))
#define PM_WDOG         ((volatile unsigned int*)(MMIO_BASE + 0x00100024))
#define PM_PASSWORD     0x5A000000
#define PM_RSTC_FULLRST 0x00000020

#endif
