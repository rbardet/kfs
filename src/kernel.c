#include "debug/printk.h"
#include "switch_screen/switch_screen.h"

void kmain() {
	terminal_initialize();
	printk("Terminal 0: Hello, World!\n");
	long long i = 0;
	while (1) {
		if (i < 1000000000) {
			i++;
		} else {
			break;
		}
	}
	switch_terminal(1);
	printk("Terminal 1: This is terminal 1.\n");
	i = 0;
	while (1) {
		if (i < 1000000000) {
			i++;
		} else {
			break;
		}
	}
	switch_terminal(0);
	printk("Terminal 0: Back to terminal 0.\n");
	printk("Show buffer of terminal 1 :\n");
	i = 0;
	while (1) {
		if (i < 1000000000) {
			i++;
		} else {
			break;
		}
	}
	switch_terminal(3);
	printk("Terminal 3: This is terminal 3.\n");
	printk("Show buffer of terminal 3 :\n");
	i = 0;
	while (1) {
		if (i < 1000000000) {
			i++;
		} else {
			break;
		}
	}
	switch_terminal(8);
	printk("Terminal 8: This is terminal 8.\n");
	i = 0;
	while (1) {
		if (i < 1000000000) {
			i++;
		} else {
			break;
		}
	}
	switch_terminal(0);
	printk("Terminal 0: Back to terminal 0 again.\n");
	return;
}