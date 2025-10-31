#include "shell.h"
#include "switch_screen.h"

void shell(char *buffer, uint32 limit) {
	uint32 i = 0;
	uint8 scancode = 0;
	uint32 len = 0;

	while (1) {
		scancode = read_scancode();

		if (scancode & KEY_RELEASE) {
			continue ;
		}

		if (scancode == 75) {
			move_cursor(LEFT);
			i--;
			continue ;
		}

		if (scancode == 77) {
			if (i < len) {
				i++;
			}
			move_cursor(RIGHT);
			continue ;
		}


		char key = keyboard_map[scancode];
		if (!key) {
			continue;
		}

		if (key == '\n') {
			buffer[len] = '\0';
			printk("\n");
			execute_command(buffer);
			return;
		}

		if (key == '\b') {
			if (i > 0) {
				i--;
				column--;
				vga[line * WIDTH + (column)] = ' ' | tty_color;
				update_cursor();
			}
			continue;
		}

		buffer[i++] = key;
		printk("%c", key);
		update_cursor();
		if (i >= limit - 1) {
			buffer[i] = '\0';
			printk("\n");
			return;
		}

		len++;
	}
}