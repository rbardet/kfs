#include "print.h"

void print_terminal(const char *text, unsigned int color) {
	char *vmem = VRAM;
	while (text) {
		*vmem++ = *text++;
		*vmem++ = color;
	}
	return ;
}