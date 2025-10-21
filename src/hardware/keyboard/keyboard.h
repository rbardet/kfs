#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_PORT 0x60

#include "../../graphic/printk.h"
#include "../../interrupt/idt.h"

static const char keyboard_map[128] = {
	0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b',
	'\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
	0,'a','s','d','f','g','h','j','k','l',';','\'','`',
	0,'\\','z','x','c','v','b','n','m',',','.','/',0,
	'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void keyboard_interrupt();

#endif
