#include "shell.h"

// https://wiki.osdev.org/Text_Mode_Cursor

#define CURSOR_REGISTER_SELECTOR 0x3D4
#define CURSOR_VALUE_PORT 0x3D5

#define CURSOR_LOW 0x0F
#define CURSOR_HIGH 0x0E

void update_cursor() {
	u16 pos = line * WIDTH + column;

	outb(CURSOR_REGISTER_SELECTOR, CURSOR_LOW);
	outb(CURSOR_VALUE_PORT, (u8) (pos & 0xFF));
	outb(CURSOR_REGISTER_SELECTOR, CURSOR_HIGH);
	outb(CURSOR_VALUE_PORT, (u8) ((pos >> 8) & 0xFF));
}

void move_cursor(arrow dir) {
	if ((column == 0 && dir == LEFT) || (column == WIDTH && dir == RIGHT)) {
		return ;
	}

	if (dir == LEFT) {
		column--;
		update_cursor();
		return ;
	}

	if (dir == RIGHT) {
		column++;
		update_cursor();
		return ;
	}
}