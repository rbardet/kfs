#include "gdt.h"

// https://wiki.osdev.org/GDT_Tutorial

GDT_TABLE gdt[GDT_ENTRY_SIZE] __attribute__((section(".gdt")));

static void create_table(u32 base, u32 limit, u16 access, u8 flags, u32 entry) {
	gdt[entry].limit = (limit & 0xFFFF);
	gdt[entry].low_base = (base & 0xFFFF);
	gdt[entry].middle_base = (base >> 16) & 0xFF;
	gdt[entry].access = access;
	gdt[entry].flags = (limit >> 16) & 0x0F;
	gdt[entry].flags |= ((flags << 4) & 0xF0);
	gdt[entry].high_base = (base >> 24) & 0xFF;
}

void init_gdt() {
	GDT_PTR *gdt_ptr = (GDT_PTR *)GDT_ADRESS;
	gdt_ptr->limit = (sizeof(GDT_TABLE) * GDT_ENTRY_SIZE) - 1;
	gdt_ptr->base = (u32)&gdt;
	create_table(0, 0, 0, 0, 0);
	create_table(0, 0xFFFFF, (u16)GDT_KERNEL_CODE, (u8)SEG_DEFAULT_FLAGS, 1);
	create_table(0, 0xFFFFF, (u16)GDT_KERNEL_DATA, (u8)SEG_DEFAULT_FLAGS, 2);
	create_table(0, 0xFFFFF, (u16)GDT_KERNEL_STACK, (u8)SEG_DEFAULT_FLAGS, 3);
	create_table(0, 0xFFFFF, (u16)GDT_USER_CODE, (u8)SEG_DEFAULT_FLAGS, 4);
	create_table(0, 0xFFFFF, (u16)GDT_USER_DATA, (u8)SEG_DEFAULT_FLAGS, 5);
	create_table(0, 0xFFFFF, (u16)GDT_KERNEL_STACK, (u8)SEG_DEFAULT_FLAGS, 6);
	load_gdt((u32)gdt_ptr);
}