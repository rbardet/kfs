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
global enable_interrupt
extern kmain
extern keyboard_interrupt
start:
	CALL kmain
HaltKernel:
	JMP HaltKernel
keyboard_handler:
	PUSHA
	CALL keyboard_interrupt
	MOV al, 0x20
	OUT 0x20, al
	POPA
	IRETD

enable_interrupt:
	STI
	RET
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
	mov edx, [esp + 4]
	lidt [edx]
	ret