#include "graphic/printk.h"
#include "graphic/switch_screen.h"
#include "interrupt/idt.h"
#include "hardware/keyboard/keyboard.h"
#include "lib/lib.h"

void kmain() {
	terminal_initialize();
	printk("Starting...\n");
	
	init_idt();
	printk("IDT loaded\n");
	
	init_kb();
	printk("KB initialized\n");
		
	// enable_interrupt();
	// printk("Interrupts enabled!\n");
}