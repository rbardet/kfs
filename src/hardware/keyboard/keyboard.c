#include "keyboard.h"

void keyboard_interrupt() {
	char key = inb(KEYBOARD_PORT);
	if (key >= 128) {
		return ;
	}
	char c = keyboard_map[key];
	printk("%c", c);
}