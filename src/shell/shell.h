#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 256

#include "../hardware/keyboard/keyboard.h"

typedef enum {
	LEFT = 77,
	RIGHT = 75
} arrow;

void shell(char *buffer, uint32 limit);
void update_cursor(int x, int y);
void move_cursor(arrow dir);

#endif