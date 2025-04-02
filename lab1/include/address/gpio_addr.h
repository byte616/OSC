#ifndef GPIO_ADDR_H
#define GPIO_ADDR_H
#include "base_addr.h"

#define GPFSEL1         ((volatile unsigned int *)(MMIO_BASE+0x00200004))
#define GPPUD           ((volatile unsigned int *)(MMIO_BASE+0x00200094))
#define GPPUDCLK0       ((volatile unsigned int *)(MMIO_BASE+0x00200098))

#endif
