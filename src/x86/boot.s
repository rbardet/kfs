section .text
	ALIGN 4
	DD 0x1BADB002
	DD 0x00000000
	DD -(0x1BADB002 + 0x00000000)

global start
global load_gdt
extern kmain
start:
	CALL kmain

load_gdt:
	MOV eax, [esp + 4]
	LGDT [eax]
	MOV ax, 0x10
	MOV ds, ax
	MOV es, ax
	MOV fs, ax
	MOV gs, ax
	MOV ax, 0x18
	MOV ss, ax
	JMP 0x08:.reload
	RET
.reload:
	RET