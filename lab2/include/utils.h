#ifndef UTILS_H
#define UTILS_H

int strcmp(const char *s1, const char *s2);
void uint2hexstr(char *output, unsigned int num);
void to_string(char *output, unsigned int num);
void swap(char *a, char *b);

// for reboot
void set(long addr, unsigned int value);
void reset(int tick);

#endif
