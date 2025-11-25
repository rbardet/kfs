#include "idt.h"

IDT32 idt;

void init_idt() {
	IDT_PTR *idt_ptr;
	idt_ptr->limit = (sizeof(IDT32) * IDT_ENTRY) - 1;
	idt_ptr->base = (u32)&idt;
    return ;
}
