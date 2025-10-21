#include "keyboard.h"

void keyboard_interrupt() {
	outb(0x20, PIC1_CMD_PORT);
	char key = inb(KEYBOARD_PORT);
	if (key >= 128) {
		return ;
	}
	char c = keyboard_map[key];
	printk("%c", c);
}