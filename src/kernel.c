#include "printk.h"
#include "switch_screen.h"
#include "keyboard.h"
#include "shell.h"
#include "lib.h"
#include "gdt.h"
#include "idt.h"

void kmain() {
	init_gdt();
	init_idt();
	u8 buffer[BUFFER_SIZE];
	terminal_initialize();
	set_print_color(COLOR_LIGHT_BLUE);
	printk(" /$$   /$$  /$$$$$$        /$$   /$$ /$$$$$$$$ /$$$$$$\n");
	printk("| $$  | $$ /$$__  $$      | $$  /$$/| $$_____//$$__  $$\n");
	printk("| $$  | $$|__/  \\ $$      | $$ /$$/ | $$     | $$  \\__/\n");
	printk("| $$$$$$$$  /$$$$$$/      | $$$$$/  | $$$$$  |  $$$$$$ \n");
	printk("|_____  $$ /$$____/       | $$  $$  | $$__/   \\____  $$\n");
	printk("      | $$| $$            | $$\\  $$ | $$      /$$  \\ $$\n");
	printk("      | $$| $$$$$$$$      | $$ \\  $$| $$     |  $$$$$$/\n");
	printk("      |__/|________/      |__/  \\__/|__/      \\______/ \n");

	khexdump((void *)GDT_ADRESS, 16);
	while (1) {
		printk(">");
		update_cursor();
		memset(buffer, 0, sizeof(buffer));
		shell(buffer, sizeof(buffer));
	}
}