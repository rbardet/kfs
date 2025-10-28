#include "printk.h"
#include "switch_screen.h"
#include "keyboard.h"
#include "shell.h"
#include "lib.h"

void kmain() {
	uint8 buffer[BUFFER_SIZE];
	terminal_initialize();
	set_print_color(COLOR_LIGHT_MAGENTA);
	printk("42 - kfs1\n");

	while (1) {
		printk("> ");
		update_cursor(column, line);
		memset(buffer, 0, sizeof(buffer));
		shell(buffer, sizeof(buffer));
	}
}
