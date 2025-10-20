#ifndef PRINTK_H
#define PRINTK_H

#define VRAM 0xb8000

#include "../lib/lib.h"
#include "stdarg.h"

#define WIDTH 80
#define HEIGHT 25



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

extern uint16 tty_color;
extern uint16 *vga;
extern uint16 column;
extern uint16 line;

typedef enum {
	KERN_EMERG,
	KERN_ALERT,
	KERN_CRIT,
	KERN_ERR,
	KERN_WARNING,
	KERN_NOTICE,
	KERN_INFO,
	KERN_DEBUG,
} kinfo;

void set_print_color(unsigned int color);
int printk(const char *format, ...);
void reset();

#endif