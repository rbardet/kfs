section .text
	ALIGN 4
	DD 0x1BADB002
	DD 0x00000000
	DD -(0x1BADB002 + 0x00000000)

global start
global inb
global outb
extern kmain

start:
	CALL kmain
inb:
	MOV edx, [esp + 4]
	IN al, dx
	RET

outb:
	MOV eax, [esp + 4]
	MOV edx, [esp + 8]
	OUT dx, al
	RET