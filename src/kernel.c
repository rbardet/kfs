#include "graphic/printk.h"
#include "graphic/switch_screen.h"
#include "hardware/keyboard/keyboard.h"
#include "shell/shell.h"
#include "lib/lib.h"

void kmain() {
	uint8 buffer[BUFFER_SIZE];
	terminal_initialize();
	set_print_color(COLOR_LIGHT_MAGENTA);
	printk("42 - kfs1\n");

	while (1) {
		printk("> ");
		memset(buffer, 0, sizeof(buffer));
		shell(buffer, sizeof(buffer));
	}
}
