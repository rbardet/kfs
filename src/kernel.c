#include "graphic/terminal/print.h"

void kmain() {
	clear_terminal();
	print_terminal("42", LIGHT_MAGENTA);
	return ;
}
