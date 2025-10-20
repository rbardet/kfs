#ifndef LIB_H
#define LIB_H

#include "type.h"

size_t strlen(const char *s);
void *memset(void *s, int c, size_t n);
char *itoa(int value, char *str);

#endif