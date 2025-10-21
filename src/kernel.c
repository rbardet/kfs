#include "graphic/printk.h"
#include "graphic/switch_screen.h"
#include "interrupt/idt.h"
#include "hardware/keyboard/keyboard.h"
#include "lib/lib.h"

void kmain() {
	terminal_initialize();
	init_idt();
	set_idt_gate();
	init_kb();
	set_print_color(COLOR_GREEN);
	// while (1) {
	// 	int i = inb(KEYBOARD_PORT);
	// 	if (i) {
	// 		char c = keyboard_map[i];
	// 		printk("%c\n", c);
	// 	}
	// }
	printk("TESSSST");
	return;
}