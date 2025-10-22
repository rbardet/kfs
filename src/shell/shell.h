#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 256

#include "../hardware/keyboard/keyboard.h"

void shell(char *buffer, uint32 limit);

#endif