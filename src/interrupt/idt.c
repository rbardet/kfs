#include "idt.h"

struct idt_entry idtt[IDT_SIZE];

void init_kb() {
	outb(0xFD, PIC1_DATA_PORT);
}

void init_idt() {
	uint32 offset = (uint32)(&keyboard_handler);

	idtt[0x21].offset_low = offset & 0xFFFF;
	idtt[0x21].selector = 0x08;
	idtt[0x21].zero = 0;
	idtt[0x21].type_attr  = 0x8E;
	idtt[0x21].offset_high = (offset >> 16) & 0xFFFF;

	struct idt_ptr idt_p;
	idt_p.limit = sizeof(struct idt_entry) * IDT_SIZE - 1;
	idt_p.base  = (uint32)&idtt;

	load_idt((uint32 *)&idt_p);
	outb(0x11, PIC1_CMD_PORT);
	outb(0x11, PIC2_CMD_PORT);

	outb(0x20, PIC1_DATA_PORT);
	outb(0x28, PIC2_DATA_PORT);

	outb(0x04, PIC1_DATA_PORT);
	outb(0x02, PIC2_DATA_PORT);

	outb(0x01, PIC1_DATA_PORT);
	outb(0x01, PIC2_DATA_PORT);
	outb(0xFF, PIC1_DATA_PORT);
	outb(0xFF, PIC2_DATA_PORT);
}