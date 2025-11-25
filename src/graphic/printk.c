#include "printk.h"

u16 tty_color = COLOR_WHITE << 8;
u16 *vga = (u16 *)VRAM;
u16 column = 0;
u16 line = 0;

void set_print_color(unsigned int color) {
	tty_color = color << 8;
}

void reset() {
	line = 0;
	column = 0;
	for (u16 y = 0; y < HEIGHT; y++) {
		for (u16 x = 0; x < WIDTH; x++) {
			vga[y * WIDTH + x] = 0 | tty_color;
		}
	}
}

static void scroll() {
	for (u16 y = 0; y < HEIGHT; y++) {
		for (u16 x = 0; x < WIDTH; x++) {
			vga[(y - 1) * WIDTH + x] = vga[y * WIDTH + x];
		}
	}
	
	for (u16 x = 0; x < HEIGHT; x++) {
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
			u16 tabLen = 4 - (column % 4);
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

static void convert(u64 nb, const char *base) {
	if (nb >= 16) {
		convert(nb / 16, base);
		convert(nb % 16, base);
	}
	else {
		printk("%c", base[nb]);
	}
}

static int puthexk(u32 nb, bool isUpper) {
	int				len;
	unsigned int	tmp;
	char			*base;

	if (isUpper) {
		base = HEXA_BASE_UPPER;
	} else {
		base = HEXA_BASE_LOWER;
	}

	len = 0;
	tmp = nb;
	if (nb == 0)
		len = 1;
	else {
		while (tmp != 0) {
			tmp /= 16;
			len++;
		}
	}
	convert(nb, base);
	return (len);
}

static int putptrk(u64 ptr) {
	int len = 0;
	len += putstrk("0x");
	len += puthexk(ptr, false);
	return (len);
}

static int printk_format(va_list list, const char format) {
	int len = 0;

	switch (format) {
		case 'd':
			int num = va_arg(list, int);
			char buffer[12];
			itoa(num, buffer);
			return (putstrk(buffer));
			break;
		case 'c':
			print_terminal(va_arg(list, int));
			return (1);
			break;
		case 's':
			const char *str = va_arg(list, const char *);
			return (putstrk(str));
		case 'x':
			return(puthexk(va_arg(list, u64), false));
		case 'X':
			return(puthexk(va_arg(list, u64), true));
		case 'p':
			return(putptrk(va_arg(list , u64)));
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