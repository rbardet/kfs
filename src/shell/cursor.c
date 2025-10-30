#include "shell.h"

// https://wiki.osdev.org/Text_Mode_Cursor

void update_cursor() {
	uint16 pos = line * WIDTH + column;

	outb(0x0F, 0x3D4);
	outb((uint8) (pos & 0xFF), 0x3D5);
	outb(0x0E, 0x3D4);
	outb((uint8) ((pos >> 8) & 0xFF), 0x3D5);
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