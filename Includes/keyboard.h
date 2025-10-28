#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEY_RELEASE 0x80

#include "printk.h"
#include "lib.h"

static const char keyboard_map[128] = {
	0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b',
	'\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
	0,'a','s','d','f','g','h','j','k','l',';','\'','`',
	0,'\\','z','x','c','v','b','n','m',',','.','/',0,
	'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,
	0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0
};

extern uint8 inb(uint16 port);
extern void outb(uint8 value, uint16 port);
uint8 read_scancode();

#endif
