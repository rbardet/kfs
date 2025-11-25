#ifndef PRINTK_H
#define PRINTK_H

#define VRAM 0xb8000

#include "lib.h"
#include <stdarg.h>

#define WIDTH 80
#define HEIGHT 25

#define HEXA_BASE_LOWER "0123456789abcdef"
#define HEXA_BASE_UPPER "0123456789ABCDEF"

typedef enum {
	COLOR_BLACK,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_MAGENTA,
	COLOR_BROWN,
	COLOR_LIGHT_GRAY,
	COLOR_DARK_GRAY,
	COLOR_LIGHT_BLUE,
	COLOR_LIGHT_GREEN,
	COLOR_LIGHT_CYAN,
	COLOR_LIGHT_RED,
	COLOR_LIGHT_MAGENTA,
	COLOR_YELLOW,
	COLOR_WHITE
} color;

extern u16 tty_color;
extern u16 *vga;
extern u16 column;
extern u16 line;

void set_print_color(unsigned int color);
int printk(const char *format, ...);
void reset();

#endif