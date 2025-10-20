#include "printk.h"

uint16 tty_color = COLOR_WHITE << 8;
uint16 *vga = (uint16 *)VRAM;
uint16 column = 0;
uint16 line = 0;

void set_print_color(unsigned int color) {
	tty_color = color << 8;
}

void reset() {
	line = 0;
	column = 0;
	for (uint16 y = 0; y < HEIGHT; y++) {
		for (uint16 x = 0; x < WIDTH; x++) {
			vga[y * WIDTH + x] = ' ' | tty_color;
		}
	}
	
}

static void scroll() {
	for (uint16 y = 0; y < HEIGHT; y++) {
		for (uint16 x = 0; x < WIDTH; x++) {
			vga[(y - 1) * WIDTH + x] = vga[y * WIDTH + x];
		}
	}
	
	for (uint16 x = 0; x < HEIGHT; x++) {
		vga[(HEIGHT - 1) * WIDTH + x] = ' ' | tty_color;
	}
}

static void newLine() {
	if (line < HEIGHT - 1) {
		line++;
		column = 0;
	} else {
		scroll();
		column = 0;
	}
}

void print_terminal(const char text) {
	switch (text) {
		case '\n':
			newLine();
			break;
		case '\r':
			column = 0;
			break;
		case '\t':
			if (column == WIDTH) {
				newLine();
			}
			uint16 tabLen = 4 - (column % 4);
			while (tabLen != 0) {
				vga[line * WIDTH + (column++)] = ' ' | tty_color;
				tabLen--;
			}
			break;
		default:
			if (column == WIDTH) {
				newLine();
			}
			vga[line * WIDTH + (column++)] = text | tty_color;
			break ;
	}
}

static int putstrk(const char *str) {
	int len = 0;
	while (*str) {
		print_terminal(*str);
		len++;
		str++;
	}
	return (len);
}

static int printk_format(va_list list, const char format) {
	int len = 0;

	switch (format) {
		// case 'c':
		// 	print_terminal(va_arg(list, char));
		// 	return (1);
		case 's':
			const char *str = va_arg(list, char *);
			return (putstrk(str));
	}
	return (len);
}

int printk(const char *format, ...) {
	va_list arg;
	int len = 0;

	va_start(arg, format);
	while (*format) {
		if (*format == '%' && *(format + 1)) {
			len += printk_format(arg, *(format + 1));
			format += 2;
		} else {
			print_terminal(*format);
			format++;
			len++;
		}
	}
	va_end(arg);

	return (len);
}