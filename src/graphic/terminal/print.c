#include "print.h"

void clear_terminal() {
	uint16 *vmem = (uint16 *)VRAM;
	for (size_t y = 0; y < HEIGHT; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			vmem[y * WIDTH + x] = ' ' | (BLACK << 8);
		}
	}
}

void print_terminal(const char *text, unsigned int color) {
	uint16 *vmem = (uint16 *)VRAM;
	while (*text) {
		*vmem++ = *text++ | (color << 8);
	}
	return ;
}