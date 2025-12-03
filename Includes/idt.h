#ifndef IDT_H
#define IDT_H

#include "lib.h"

#define IDT_ENTRY 256

typedef struct {
   u16 offset_1;        // offset bits 0..15
   u16 selector;        // a code segment selector in GDT or LDT
   u8  zero;            // unused, set to 0
   u8  type_attributes; // gate type, dpl, and p fields
   u16 offset_2;        // offset bits 16..31
} __attribute__((packed)) IDT32;

typedef struct {
	u16 limit;
	u32 base;
}  __attribute__((packed)) IDT_PTR;

extern void load_idt(u32 idt_ptr);
void init_idt();

#endif