#include "shell.h"

// https://wiki.osdev.org/Text_Mode_Cursor

void update_cursor() {
	u16 pos = line * WIDTH + column;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (u8) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (u8) ((pos >> 8) & 0xFF));
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