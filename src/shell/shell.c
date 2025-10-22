#include "shell.h"

// https://wiki.osdev.org/Text_Mode_Cursor
static void update_cursor(int x, int y) {
	uint16 pos = y * WIDTH + x;

	outb(0x0F, 0x3D4);
	outb((uint8) (pos & 0xFF), 0x3D5);
	outb(0x0E, 0x3D4);
	outb((uint8) ((pos >> 8) & 0xFF), 0x3D5);
}

#define CLR_INDEX 6

void shell(char *buffer, uint32 limit) {
	uint32 i = 0;
	uint8 scancode = 0;
	
	while (1) {
		update_cursor(column, line);
		scancode = read_scancode();

		if (scancode & KEY_RELEASE) {
			continue;
		}

		char key = keyboard_map[scancode];
		if (!key) {
			continue;
		}
		
		if (strncmp(buffer, "color=", 6) == 0) {
			uint8 c = buffer[CLR_INDEX];
			if (c >= '1' && c <= '9') {
				set_print_color(c - '0');
				buffer[i] = '\0';
				printk("\n");
				return;
			}
		}

		if (key == '\n') {
			buffer[i] = '\0';
			printk("\n");
			return;
		}

		if (key == '\b') {
			if (i > 0) {
				i--;
				column--;
				vga[line * WIDTH + (column)] = ' ' | tty_color;
			}
			continue;
		}

		buffer[i++] = key;
		printk("%c", key);
		if (i >= limit - 1) {
			buffer[i] = '\0';
			return;
		}
	}
}