section .text
	ALIGN 4
	DD 0x1BADB002
	DD 0x00000000
	DD -(0x1BADB002 + 0x00000000)

global start
extern kmain

start:
	CALL kmain
HaltKernel:
	JMP HaltKernel