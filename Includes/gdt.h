#ifndef GDT_H
#define GDT_H

#include "lib.h"
#include "printk.h"

// https://wiki.osdev.org/GDT_Tutorial

#define SEG_DESCTYPE(x) ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x) ((x) << 0x07) // Present
#define SEG_SAVL(x) ((x) << 0x0C) // Available for system use
#define SEG_LONG(x) ((x) << 0x0D) // Long mode
#define SEG_SIZE(x) ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x) ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x) (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)
 
#define SEG_DATA_RDWR 0x02 // Read/Write
#define SEG_CODE_EXRD 0x0A // Execute/Read
#define SEG_DEFAULT_FLAGS 0xCF 

#define GDT_KERNEL_CODE SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
					SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | \
					SEG_PRIV(0) | SEG_CODE_EXRD
 
#define GDT_KERNEL_DATA SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
					SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | \
					SEG_PRIV(0) | SEG_DATA_RDWR

#define GDT_KERNEL_STACK GDT_KERNEL_DATA

#define GDT_USER_CODE SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
					SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | \
					SEG_PRIV(3) | SEG_CODE_EXRD
 
#define GDT_USER_DATA SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
					SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | \
					SEG_PRIV(3) | SEG_DATA_RDWR

#define GDT_USER_STACK GDT_USER_DATA

#define GDT_ENTRY_SIZE 7

typedef struct {
	uint16	limit;
	uint16	low_base;
	uint8	middle_base;
	uint8	access;
	uint8	flags;
	uint8	high_base;
}  __attribute__((packed)) GDT_TABLE;

typedef struct {
	uint16 limit;
	uint32 base;
}  __attribute__((packed)) GDT_PTR;

extern void load_gdt(uint32 gdt);
void init_gdt();
extern void *get_stack_top();

#endif