#include "debug/printk.h"

void kmain() {
	reset();
	set_print_color(COLOR_MAGENTA);

	const char *str = "TESSSSSSSSSSSSST";
	printk("%s\n", str);
	for (int i = 0; i < 30; i++)
		printk("Line number %d\n", i);
	return ;
}