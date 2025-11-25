#include "lib.h"

static void print_hex_byte(u8 b) {
	const u8 *hex = HEXA_BASE_UPPER;
	printk("%c%c ", hex[b >> 4], hex[b & 0xF]);
}

static void print_hex_addr(u32 addr) {
	const u8 *hex = HEXA_BASE_UPPER;
	u8 buf[9];
	u32 i;

	for (i = 0; i < 8; i++) {
		buf[7 - i] = hex[addr & 0xF];
		addr >>= 4;
	}
	buf[8] = '\0';
	printk("%s: ", buf);
}

void khexdump(const void *data, u32 size) {
	const u8 *byte = (const u8 *)data;
	u8 ascii[17];
	u32 i, j;
	u32 base = (u32)data;

	ascii[16] = '\0';

	for (i = 0; i < size; i++) {
		if (i % 16 == 0) {
			if (i != 0)
				printk(" | %s\n", ascii);
			print_hex_addr(base + i);
		}

		print_hex_byte(byte[i]);

		if (byte[i] >= 32 && byte[i] <= 126)
			ascii[i % 16] = byte[i];
		else
			ascii[i % 16] = '.';

		if ((i % 16) == 7)
			printk(" ");
	}

	u32 remaining = i % 16;
	if (remaining != 0) {
		u32 spaces = (16 - remaining) * 3 + (remaining <= 8 ? 1 : 0);
		for (j = 0; j < spaces; j++)
			printk(" ");
		ascii[remaining] = '\0';
	} else {
		ascii[16] = '\0';
	}

	printk(" | %s\n", ascii);
}
