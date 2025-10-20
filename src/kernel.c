#include "debug/printk.h"

void kmain() {
	reset();
	set_print_color(COLOR_MAGENTA);

	const char *str = "TESSSSSSSSSSSSST";
	printk("%s\n", str);
	printk("TESTTTT\n");
	return ;
}