#include "gdt.h"

// https://wiki.osdev.org/GDT_Tutorial

GDT_TABLE gdt[GDT_ENTRY_SIZE];
GDT_PTR *gdt_ptr __attribute__((section(".gdt")));

static void create_table(uint32 base, uint32 limit, uint16 access, uint8 flags, uint32 entry) {
	gdt[entry].limit = (limit & 0xFFFF);
	gdt[entry].low_base = (base & 0xFFFF);
	gdt[entry].middle_base = (base >> 16) & 0xFF;
	gdt[entry].access = access;
	gdt[entry].flags = (limit >> 16) & 0x0F;
	gdt[entry].flags |= ((flags << 4) & 0xF0);
	gdt[entry].high_base = (base >> 24) & 0xFF;
}

void init_gdt() {
	gdt_ptr->limit = (sizeof(GDT_TABLE) * GDT_ENTRY_SIZE) - 1;
	gdt_ptr->base = (uint32)&gdt;
	create_table(0, 0, 0, 0, 0);
	create_table(0, 0xFFFFF, (uint16)GDT_KERNEL_CODE, (uint8)SEG_GRAN_1, 1);
	create_table(0, 0xFFFFF, (uint16)GDT_KERNEL_DATA, (uint8)SEG_GRAN_1, 2);
	// kernel stack
	create_table(0, 0xFFFFF, (uint16)GDT_USER_CODE, (uint8)SEG_GRAN_1, 3);
	create_table(0, 0xFFFFF, (uint16)GDT_USER_DATA, (uint8)SEG_GRAN_1, 4);
	// user stack
	load_gdt((uint32)gdt_ptr);
	printk("GDT loaded\n");
}

void print_kstack() {

}