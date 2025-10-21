section .text
	ALIGN 4
	DD 0x1BADB002
	DD 0x00000000
	DD -(0x1BADB002 + 0x00000000)

global start
global inb
global outb
global keyboard_handler
global load_idt
extern kmain
extern keyboard_interrupt
extern 
start:
	CALL kmain
HaltKernel:
	JMP HaltKernel
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
	MOV al, [esp + 4]
	MOV edx, [esp + 8]
	OUT dx, al
	RET
load_idt:
	lea edx, [idtp]
	lidt [edx]
	ret