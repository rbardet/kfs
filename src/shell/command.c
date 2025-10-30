#include "command.h"

void execute_command(char *command) {
    if (strncmp(command, "clear", 5) == 0) {
        reset();
        return;
    }

    if (strncmp(command, "color=", 6) == 0) {
        uint8 c = command[6];
        if (c >= '1' && c <= '9') {
            set_print_color(c - '0');
            return;
        } else {
            printk("Invalid color code. Use a number between 1 and 9.\n");
            return;
        }
    }

    if (strncmp(command, "terminal=", 9) == 0) {
        uint8 t = command[9] - '0';
        if (t >= 0 && t <= 9) {
            switch_terminal(t);
            return;
        } else {
            printk("Invalid terminal number. Use a number between 0 and 9.\n");
            return;
        }
    }

    if (strncmp(command, "reboot", 6) == 0) {
        printk("Rebooting system...\n");
        uint8 good = 0x02;
        while (good & 0x02)
            good = inb(0x64);
        outb(0xFE, 0x64);
        return;
    }

    if (strncmp(command, "shutdown", 8) == 0) {
        printk("Shutting down system...\n");
        outw(0x2000, 0x604);
        return;
    }

    if (strncmp(command, "halt", 4) == 0) {
        printk("Halting CPU...\n");
        // TODO: Implement halt functionality
        return;
    }

    if (strncmp(command, "help", 4) == 0) {
        printk("Available commands:\n");
        printk(" - clear: Clear the terminal screen\n");
        printk(" - help: Show this help message\n");
        printk(" - color=<1-9>: Change text color\n");
        printk(" - terminal=<0-9>: Switch to terminal number\n");
        return;
    }

    printk("Unknown command: %s\n", command);
    return;
}