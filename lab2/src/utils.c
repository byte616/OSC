#include "utils.h"
#include "mini_uart.h"

int strcmp(const char *s1, const char *s2) {
	while (*s1 && *s2 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
	return (unsigned char)*s1 - (unsigned char)*s2;
}


int strncmp(const char *s1, const char *s2, int len) {
	for(int i = 0; i < len; i++) {
		if(s1[i] != s2[i]) return 1;
	}
	return 0;
}

void uint2hexstr(char *output, unsigned int num) {
	output[0] = '0';
	output[1] = 'x';
	for(int i = 7; i >= 0; i--) {
		int idx = 7 - i + 2;
		char val = (num >> (i * 4)) & 0xF;
		output[idx] = (val < 10) ? ('0' + val) : ('a' + val - 10); 
	}
	output[10] = '\n';
	output[11] = '\0';
}

void swap(char *a, char *b) {
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void to_string(char *output, unsigned int num) {
	char *ptr = output;
	
	// special case: 0
	if(num == 0) {
		*ptr++ = '0';
		*ptr = '\0';
		return;
	}

	// convert into string
	while(num > 0) {
		unsigned int val = num % 10;
		*ptr++ = '0' + val;
		num /= 10;
	}
	*ptr = '\0';

	// reverse string
	char *head = output;
	ptr--;
	while(head < ptr) {
		swap(head, ptr);
		head++;
		ptr--;
	}
}

void set(long addr, unsigned int value) {
    volatile unsigned int* point = (unsigned int*)addr;
    *point = value;
}

void reset(int tick) {                 // reboot after watchdog timer expire
    set(PM_RSTC, PM_PASSWORD | 0x20);  // full reset
    set(PM_WDOG, PM_PASSWORD | tick);  // number of watchdog tick
}
