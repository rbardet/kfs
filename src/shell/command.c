#include "command.h"

static void switch_color(uint8 c) {
	if (c >= '1' && c <= '9') {
		set_print_color(c - '0');
		return;
	} else {
		printk("Invalid color code. Use a number between 1 and 9.\n");
		return;
	}
}

static void terminal_switch(uint8 t) {
	if (t >= 0 && t <= 9) {
		switch_terminal(t);
		return;
	} else {
		printk("Invalid terminal number. Use a number between 0 and 9.\n");
		return;
	}
}

static void reboot() {
	printk("Rebooting system...\n");
	uint8 good = 0x02;
	while (good & 0x02) 
		good = inb(0x64);
	outb(0xFE, 0x64);
	return;
}

static void shutdown() {
	printk("Shutting down system...\n");
	outw(0x2000, 0x604);
	return;
}

static void help() {
	printk("Available commands:\n");
	printk(" - clear: Clear the terminal screen\n");
	printk(" - help: Show this help message\n");
	printk(" - color=<1-9>: Change text color\n");
	printk(" - terminal=<0-9>: Switch to terminal number\n");
	return;
}

void execute_command(char *command) {
	if (strcmp(command, "clear") == 0) {
		reset();
		return;
	}

	if (strncmp(command, "color=", 6) == 0) {
		uint8 c = command[6];
		switch_color(c);
		return ;
	}

	if (strncmp(command, "terminal=", 9) == 0) {
		uint8 t = command[9] - '0';
		terminal_switch(t);
		return ;
	}

	if (strcmp(command, "reboot") == 0) {
		reboot();
		return ;
	}

	if (strcmp(command, "shutdown") == 0) {
		shutdown();
		return ;
	}

	if (strcmp(command, "halt") == 0) {
		printk("Halting CPU...\n");
		// TODO: Implement halt functionality
		return;
	}

	if (strcmp(command, "help") == 0) {
		help();
		return ;
	}

	if (strcmp(command, "stack") == 0) {
		khexdump(get_stack_top(), 20);
		return;
	}

	printk("Unknown command: %s\n", command);
	return;
}