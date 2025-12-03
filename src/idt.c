#include "idt.h"

// https://wiki.osdev.org/Interrupt_Descriptor_Table

IDT32 idt[IDT_ENTRY];

static void create_table(u32 offset, u16 selector, u8 type, u32 entry) {
	idt[entry].offset_1 = offset & 0xFFFF;
	idt[entry].zero = 0;
	idt[entry].selector = selector;
	idt[entry].type_attributes = type;
	idt[entry].offset_2 = (offset >> 16) & 0xFFFF;
}

void init_idt() {
	IDT_PTR *idt_ptr;
	idt_ptr->limit = (sizeof(IDT32) * IDT_ENTRY) - 1;
	idt_ptr->base = (u32)&idt;

	load_idt((u32)idt_ptr);
	return ;
}