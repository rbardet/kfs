#ifndef PRINT_H
#define PRINT_H

#define VRAM (char *)0xb8000

#include "../../lib/string/string.h"

void print_terminal(const char *text, int forecolour, int backcolour);

#endif