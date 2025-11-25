#include "keyboard.h"

u8 read_scancode() {
	while (!(inb(KEYBOARD_STATUS_PORT) & 0x01));
	return (inb(KEYBOARD_DATA_PORT));
}
