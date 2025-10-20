section .text
	ALIGN 4
	DD 0x1BADB002
	DD 0x00000000
	DD -(0x1BADB002 + 0x00000000)

global start
global inb
global outb

extern kmain
extern keyboard_interrupt
start:
	CALL kmain

keyboard_handler:
	PUSHAD
	CALL keyboard_interrupt
	POPAD
	IRETD

inb:
	MOV edx, [esp + 4]
	IN al, dx
	RET

outb:
	MOV edx, [esp + 4]
	MOV ebx, [esp + 8]
	OUT dx, al
	RET

