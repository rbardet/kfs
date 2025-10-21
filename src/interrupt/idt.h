#ifndef IDT_H
#define IDT_H

#define PIC1_CMD_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_CMD_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

#define IDT_SIZE 256

#include "../lib/lib.h"
#include "../hardware/keyboard/keyboard.h"

struct idt_entry {
	uint16 offset_low;
	uint16 selector;
	uint8 zero;
	uint8 type_attr;
	uint16 offset_high;
} __attribute__((packed));

struct idt_ptr {
	uint16 limit;
	uint32 base;
} __attribute__((packed));

extern uint8 inb(uint16 port);
extern void outb(uint8 value, uint16 port);
extern void load_idt(uint32 *idt_adress);
void init_idt();
void init_kb();
void set_idt_gate();

#endif