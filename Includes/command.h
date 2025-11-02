#ifndef COMMAND_H
# define COMMAND_H

#include "printk.h"
#include "lib.h"
#include "switch_screen.h"
#include "keyboard.h"
#include "gdt.h"

#define SIG_SHUTDOWN 0x2000
#define ACPI_PORT 0x604

void execute_command(char *command);
extern void halt();

#endif
