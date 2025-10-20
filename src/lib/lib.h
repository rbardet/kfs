#ifndef LIB_H
#define LIB_H

#define uint16 unsigned short
#define size_t long unsigned int

size_t strlen(const char *s);
void *memset(void *s, int c, size_t n);
char *itoa(int value, char *str);

#endif