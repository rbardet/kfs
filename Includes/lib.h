#ifndef LIB_H
#define LIB_H

#include <stddef.h>

#define int8 signed char
#define uint8 unsigned char
#define int16 short
#define uint16 unsigned short
#define int32 int
#define uint32 unsigned int
#define int64 long long
#define uint64 unsigned long long

size_t strlen(const char *s);
void *memset(void *s, int c, size_t n);
char *itoa(int value, char *str);
int	strcmp(char *s1, char *s2);
int	strncmp(char *s1, char *s2, size_t n);

#endif