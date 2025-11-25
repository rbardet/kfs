#ifndef LIB_H
#define LIB_H

#include <stddef.h>

#define i8 signed char
#define u8 unsigned char
#define i16 short
#define u16 unsigned short
#define i32 int
#define u32 unsigned int
#define i64 long long
#define u64 unsigned long long

#include "printk.h"

typedef enum {
	false,
	true
}	bool;

size_t strlen(const char *s);
void *memset(void *s, int c, size_t n);
char *itoa(int value, char *str);
int	strcmp(char *s1, char *s2);
int	strncmp(char *s1, char *s2, size_t n);
void khexdump(const void *data, u32 size);

#endif