#ifndef LIB_H
#define LIB_H

#include <stddef.h>

#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned int
#define uint64 unsigned long long

size_t strlen(const char *s);
void *memset(void *s, int c, size_t n);
char *itoa(int value, char *str);

#endif