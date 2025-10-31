#ifndef COMMAND_H
# define COMMAND_H

#include "printk.h"
#include "lib.h"
#include "switch_screen.h"
#include "keyboard.h"
#include "gdt.h"

void execute_command(char *command);
extern void halt();

#endif
