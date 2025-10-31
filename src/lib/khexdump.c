#include "lib.h"

static void print_hex_byte(uint8 b) {
	const uint8 *hex = HEXA_BASE_UPPER;
	printk("%c%c ", hex[b >> 4], hex[b & 0xF]);
}

static void print_hex_addr(uint32 addr) {
	const uint8 *hex = HEXA_BASE_UPPER;
	uint8 buf[9];
	uint32 i;

	for (i = 0; i < 8; i++) {
		buf[7 - i] = hex[addr & 0xF];
		addr >>= 4;
	}
	buf[8] = '\0';
	printk("%s: ", buf);
}

void khexdump(const void *data, uint32 size) {
	const uint8 *byte = (const uint8 *)data;
	uint8 ascii[17];
	uint32 i, j;
	uint32 base = (uint32)data;

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

	uint32 remaining = i % 16;
	if (remaining != 0) {
		uint32 spaces = (16 - remaining) * 3 + (remaining <= 8 ? 1 : 0);
		for (j = 0; j < spaces; j++)
			printk(" ");
		ascii[remaining] = '\0';
	} else {
		ascii[16] = '\0';
	}

	printk(" | %s\n", ascii);
}
