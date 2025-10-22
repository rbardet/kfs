#include "shell.h"
#include "../graphic/switch_screen.h"

#define CLR_INDEX 6

void shell(char *buffer, uint32 limit) {
	uint32 i = 0;
	uint8 scancode = 0;
	
	while (1) {
		scancode = read_scancode();

		if (scancode & KEY_RELEASE) {
			continue;
		}

		if (scancode == 75) {
			move_cursor(LEFT);
			continue ;
		}

		if (scancode == 77) {
			move_cursor(RIGHT);
			continue ;
		}

		if (scancode > 1 && scancode <= 10)
		{
			switch_terminal(scancode - 2);
			printk("\n> ");
			update_cursor(column, line);
			continue ;
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
				update_cursor(column, line);
			}
			continue;
		}

		buffer[i++] = key;
		printk("%c", key);
		update_cursor(column, line);
		if (i >= limit - 1) {
			buffer[i] = '\0';
			return;
		}
	}
}